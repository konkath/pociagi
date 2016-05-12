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

	pthread_mutex_init(&stopMutex, NULL);
	pthread_cond_init(&stopCond, NULL);

	timerMS = 500;

	int lines, columns;
	getmaxyx(parent, lines, columns);

	Graphics::createDerWindow(winBooth, parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1);
	Graphics::createBox(winBooth, '#', '#');

	reportStatus();

	pthread_create(&queThread, NULL, &Booth::serve, this);
}

Booth::~Booth(){
	Graphics::deleteWindow(winBooth);

	pthread_mutex_destroy(&stopMutex);
	pthread_cond_destroy(&stopCond);
}

void Booth::stopBooth(){
	stopLock();
	stop = true;
	//wait for serve to finish
	pthread_cond_wait(&stopCond, &stopMutex);
	stopUnlock();
}

void Booth::reportStatus(){
	if(free){
		Graphics::showInMiddle(winBooth, "W");
	}else{
		Graphics::showInMiddle(winBooth, "Z");
	}
}

void* Booth::serve(void* me){
	Booth* thisThread = static_cast<Booth*>(me);

	bool isStopped = false;

	while(!isStopped){
		thisThread->queue->addPeople();
		usleep(thisThread->timerMS * 1000);

		thisThread->stopLock();
		isStopped = thisThread->stop;
		thisThread->stopUnlock();
	}

	thisThread->stopLock();
	pthread_cond_signal(&thisThread->stopCond);
	thisThread->stopUnlock();

	pthread_exit(NULL);
}

int Booth::stopLock(){
	return pthread_mutex_lock(&stopMutex);
}

int Booth::stopUnlock(){
	return pthread_mutex_unlock(&stopMutex);
}

