/*
 * Booth.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booth.h>
#include <iostream>

Booth::Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que)
			:platforms(plat), queue(que){
	free = true;
	stop = false;
	timerMS = 500;

	randomGenerator = new RandomGenerator();
	stopMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	pthread_cond_init(&stopCond, NULL);

	int lines, columns;
	getmaxyx(parent, lines, columns);

	winBooth = new Graphics(parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1, '#', '#');

	reportStatus();

	pthread_create(&queThread, NULL, &Booth::serve, this);
}

Booth::~Booth(){
	pthread_join(queThread, NULL);
	pthread_cond_destroy(&stopCond);

	delete winBooth;
	delete randomGenerator;
	delete stopMutex;
}

void Booth::stopBooth(){
	stopMutex->lock();
	stop = true;
	stopMutex->unlock();
}

void Booth::reportStatus(){
	string str[1];
	if(free){
		str[0] = "W";
		winBooth->showInMiddle(str, 1);
	}else{
		str[0] = "Z";
		winBooth->showInMiddle(str, 1);
	}
}

void* Booth::serve(void* me){
	Booth* thisThread = static_cast<Booth*>(me);

	thisThread->stopMutex->lock();
	while(!thisThread->stop){
		thisThread->stopMutex->unlock();

		thisThread->free = true;

		if(thisThread->queue->isEmpty()){
			thisThread->queue->removePeople();
			thisThread->platforms->addPeople
			(thisThread->randomGenerator->getRandomInt(0, 3));
			thisThread->free = false;
		}

		thisThread->reportStatus();
		usleep(thisThread->timerMS * 1000);

		thisThread->stopMutex->lock();
	}//exit locked
	thisThread->stopMutex->unlock();

	pthread_exit(NULL);
}
