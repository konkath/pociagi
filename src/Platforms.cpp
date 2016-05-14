/*
 * Platforms.cpp
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#include <Platforms.h>

Platforms::Platforms(SignalLight* signal):signalLight(signal){
	winPlatform = new WINDOW*[nOfPlatforms];

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
	tempMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);

	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::createWindow(winPlatform[i], lines, columns, LINES - lines,
								(COLS - orgDistance) - (i * distance));
		Graphics::createBox(winPlatform[i], '|', '-');
	}

	for(int i = 0; i < nOfTrains; ++i){
		trains[i] = NULL;
	}
}

Platforms::~Platforms(){
	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::deleteWindow(winPlatform[i]);
	}

	for(int i = 0; i < nOfTrains; ++i){
		delete trains[i];
	}

	delete tempMutex;
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
	if (NULL == trains[idx]){
		trains[idx] = new Train(signalLight, getPlatform(idx), getId(idx));
	}
}

void Platforms::addRandomTrain(int idx){
	if (NULL == trains[idx]){
		int passOut = randomGenerator->getRandomInt(10, 20);
		int freeSeats = 30 - passOut;
		trains[idx] = new Train(signalLight, getPlatform(idx),
				getId(idx), passOut, freeSeats);
	}
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

	printf("co tu sie odpierdala\n");

	Graphics::showInMiddle(winPlatform[platform], str, 2);

}
