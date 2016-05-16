/*
 * Platforms.cpp
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#include <Platforms.h>

Platforms::Platforms(SignalLight* signal, Queue* queue):signalLight(signal),
	queue(queue){
	timerMS = 3000;
	stop = false;

	int lines = LINES * 0.5;
	int columns = COLS * 0.1;
	int orgDistance = COLS * 0.6;
	int distance = COLS * 0.30;

	for(int i = 0; i < nOfPlatforms; ++i){
		winPlatform[i] = new Graphics(lines, columns, LINES - lines,
								(COLS - orgDistance) - (i * distance), '|', '-');
	}

	randomGenerator = new RandomGenerator();
	peopleMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	trainMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);

	for(int i = 0; i < nOfTrains; ++i){
		trains[i] = NULL;
	}

	pthread_create(&trainThread, NULL, &Platforms::trainAdder, this);
	pthread_create(&trainRmThread, NULL, &Platforms::trainRemover, this);
}

Platforms::~Platforms(){
	trainMutex->lock();
	stop = true;
	trainMutex->unlock();

	pthread_join(trainThread, NULL);
	pthread_join(trainRmThread, NULL);

	for(int i = 0; i < nOfTrains; ++i){
		if(NULL != trains[i]){
			trains[i]->sendStop();
		}
		delete trains[i];
	}

	for(int i = 0; i < nOfPlatforms; ++i){
		delete winPlatform[i];
	}

	delete trainMutex;
	delete peopleMutex;
	delete randomGenerator;
}

void Platforms::addPeople(int idx){
	int platform = getPlatform(idx), id = getId(idx);

	peopleMutex->lock();
	people[platform].push_back(id);
	peopleMutex->unlock();

	reportStatus(idx);
}

bool Platforms::removePeople(int idx){
	int platformId = getPlatform(idx), id = getId(idx);
	bool result = false;

	peopleMutex->lock();
	if (!people[platformId].empty()){
		for(unsigned int i = 0; i < people[platformId].size(); ++i){
			if (people[platformId][i] == id){
				people[platformId].erase(people[platformId].begin() + i);
				result = true;
				break;
			}
		}
	}
	peopleMutex->unlock();

	reportStatus(idx);
	return result;
}

void Platforms::addTrain(int idx){
	trainMutex->lock();

	if (NULL == trains[idx]){
		trains[idx] = new Train(signalLight, this, queue, idx);
	}

	trainMutex->unlock();
}

bool Platforms::addRandomTrain(int idx){
	bool result = false;

	trainMutex->lock();
	if (NULL == trains[idx]){
		trainMutex->unlock();

		int passOut = randomGenerator->getRandomInt(0, 10);
		int freeSeats = 30 - passOut;
		result = true;

		trainMutex->lock();
		trains[idx] = new Train(signalLight, this, queue, idx,
								passOut, freeSeats);
	}
	trainMutex->unlock();

	return result;
}

//version for user, where green light is checked only once
void Platforms::removeTrain(int idx){
	trainMutex->lock();
	if (NULL != trains[idx] && signalLight->isGreen()){
		trains[idx]->sendStop();

		delete trains[idx];
		trains[idx] = NULL;
	}
	trainMutex->unlock();
}

int Platforms::getPlatform(int idx){
	return idx < 2 ? 0 : 1;
}

int Platforms::getId(int idx){
	return idx % 2 ? 1 : 0;
}

int Platforms::getTicketOwners(int platform, int id){
	int count = 0;

	peopleMutex->lock();
	for (unsigned int i = 0; i < people[platform].size(); ++i){
		if(people[platform][i] == id){
			count++;
		}
	}
	peopleMutex->unlock();

	return count;
}

void Platforms::reportStatus(int idx){
	int platform = getPlatform(idx);
	string str[2] = {"P: " + to_string(getTicketOwners(platform, 0)),
					 "L: " + to_string(getTicketOwners(platform, 1))};

	winPlatform[platform]->showInMiddle(str, 2);

}

void* Platforms::trainAdder(void* me){
	Platforms* thisThread = static_cast<Platforms*>(me);

	thisThread->trainMutex->lock();
	for(int i = 0; i < thisThread->nOfTrains; ++i){
		if(NULL == thisThread->trains[i]){
			thisThread->trainMutex->unlock();
			thisThread->addRandomTrain(i);
			thisThread->trainMutex->lock();
		}//exit locked

		thisThread->trainMutex->unlock();
		usleep(thisThread->timerMS * 1000);
		thisThread->trainMutex->lock();

		if(thisThread->stop){
			thisThread->trainMutex->unlock();
			pthread_exit(NULL);;
		}
	}//exit locked

	while(!thisThread->stop){
		thisThread->trainMutex->unlock();

		int rand = thisThread->randomGenerator->getRandomInt(0, 3);

		thisThread->trainMutex->lock();
		if(NULL == thisThread->trains[rand]){
			thisThread->trainMutex->unlock();

			thisThread->addRandomTrain(rand);

			thisThread->trainMutex->lock();
		}//exit locked
		thisThread->trainMutex->unlock();

		usleep(thisThread->timerMS * 1000);

		thisThread->trainMutex->lock();
	}//exit locked
	thisThread->trainMutex->unlock();

	pthread_exit(NULL);
}

void* Platforms::trainRemover(void* me){
	Platforms* thisThread = static_cast<Platforms*>(me);

	thisThread->trainMutex->lock();
	while(!thisThread->stop){
		thisThread->trainMutex->unlock();

		thisThread->signalLight->lightMutex->lock();
		pthread_cond_wait(&thisThread->signalLight->lightCond, thisThread->signalLight->lightMutex->getMutex());
		thisThread->signalLight->lightMutex->unlock();

		thisThread->trainMutex->lock();
		for(int i = 0; i < thisThread->nOfTrains; ++i){
			if(NULL != thisThread->trains[i] && thisThread->trains[i]->isReady()){
				thisThread->trainMutex->unlock();

				thisThread->removeTrain(i);

				thisThread->trainMutex->lock();
			}//exit locked
		}//exit locked
		thisThread->trainMutex->unlock();

		usleep(thisThread->timerMS * 1000);

		thisThread->trainMutex->lock();
	}//exit locked
	thisThread->trainMutex->unlock();

	pthread_exit(NULL);
}
