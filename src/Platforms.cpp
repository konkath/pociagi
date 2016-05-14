/*
 * Platforms.cpp
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#include <Platforms.h>

Platforms::Platforms(SignalLight* signal):signalLight(signal){
	winPlatform = new WINDOW*[nOfPlatforms];

	timerMS = 10000;
	stop = false;

	int lines = LINES * 0.5;
	int columns = COLS * 0.1;
	int orgDistance = COLS * 0.6;
	int distance = COLS * 0.30;

	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::createWindow(winPlatform[i], lines, columns, LINES - lines,
								(COLS - orgDistance) - (i * distance));
		Graphics::createBox(winPlatform[i], '|', '-');
	}

	people = new vector<int>[nOfPlatforms];
	trains = new Train*[nOfTrains];

	randomGenerator = new RandomGenerator();
	peopleMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	trainMutex = new Mutex(PTHREAD_MUTEX_RECURSIVE);

	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::createWindow(winPlatform[i], lines, columns, LINES - lines,
								(COLS - orgDistance) - (i * distance));
		Graphics::createBox(winPlatform[i], '|', '-');
	}

	for(int i = 0; i < nOfTrains; ++i){
		trains[i] = NULL;
	}

	pthread_create(&trainThread, NULL, &Platforms::trainAdder, this);
}

Platforms::~Platforms(){
	trainMutex->lock();
	stop = true;
	trainMutex->unlock();

	pthread_join(trainThread, NULL);

	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::deleteWindow(winPlatform[i]);
	}

	for(int i = 0; i < nOfTrains; ++i){
		delete trains[i];
	}

	delete trainMutex;
	delete peopleMutex;
	delete randomGenerator;
	delete [] winPlatform;
	delete [] people;
	delete [] trains;
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
		trains[idx] = new Train(signalLight, getPlatform(idx), getId(idx));
	}

	trainMutex->unlock();
}

bool Platforms::addRandomTrain(int idx){
	bool result = false;

	trainMutex->lock();
	if (NULL == trains[idx]){
		trainMutex->unlock();

		int passOut = randomGenerator->getRandomInt(10, 20);
		int freeSeats = 30 - passOut;
		result = true;

		trainMutex->lock();
		trains[idx] = new Train(signalLight, getPlatform(idx),
				getId(idx), passOut, freeSeats);
	}
	trainMutex->unlock();

	return result;
}

void Platforms::removeTrain(int idx){
	if (NULL != trains[idx]){
		//TODO czekac na zielone swiatlo
		delete trains[idx];
		trains[idx] = NULL;
	}
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
	string str[2] = {"L: " + to_string(getTicketOwners(platform, 0)),
					 "P: " + to_string(getTicketOwners(platform, 1))};

	Graphics::showInMiddle(winPlatform[platform], str, 2);

}

void* Platforms::trainAdder(void* me){
	Platforms* thisThread = static_cast<Platforms*>(me);

	while(true){
		thisThread->trainMutex->lock();

		for(int i = 0; i < thisThread->nOfTrains; ++i){
			if(NULL == thisThread->trains[i]){
				bool result = thisThread->addRandomTrain(i);

				if(result){
					thisThread->trainMutex->unlock();
					usleep(thisThread->timerMS * 1000);
					thisThread->trainMutex->lock();
				}
			}

			if(thisThread->stop){
				break;
			}
		}

		if(thisThread->stop){
			thisThread->trainMutex->unlock();
			break;
		}

		thisThread->trainMutex->unlock();
	}

	pthread_exit(NULL);
}
