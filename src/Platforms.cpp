/*
 * Platforms.cpp
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#include <Platforms.h>

Platforms::Platforms(SignalLight* signal):signalLight(signal){
	winPlatform = new WINDOW*[nOfPlatforms];
	people = new deque<int>[nOfPlatforms];
	trains = new Train*[nOfTrains];

	int lines = LINES * 0.5;
	int columns = COLS * 0.1;
	int orgDistance = COLS * 0.6;
	int distance = COLS * 0.30;

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

	delete [] winPlatform;
	delete [] people;
	delete [] trains;
}

void Platforms::addPeople(int idx){
	people[getPlatform(idx)].push_back(getId(idx));
	reportStatus();
}

bool Platforms::removePeople(int idx){
	int platformId = getPlatform(idx);
	if (!people[platformId].empty()){
		for(unsigned int i = 0; i < people[platformId].size(); ++i){
			if (people[platformId][i] == getId(idx)){
				people[platformId].erase(people[platformId].begin() + i);
				reportStatus();
				return true;
			}
		}
	}
	return false;
}

void Platforms::addTrain(int idx){
	if (NULL == trains[idx]){
		trains[idx] = new Train(signalLight, getPlatform(idx), getId(idx));
	}
}

void Platforms::addRandomTrain(){
	for(int i = 0; i < nOfTrains; ++i){
		if (NULL == trains[i]){
			//TODO losowy pociag
			//trains[i] = new Train();
			break;
		}
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

void Platforms::reportStatus(){
	for(int i = 0; i < nOfPlatforms; ++i){
	Graphics::showInMiddle(winPlatform[i], to_string(people[i].size()));
	}
}

