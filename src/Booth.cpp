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
	stopped = true;

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
}

void Booth::stopBooth(){
	pthread_mutex_lock(&stopMutex);
	stop = true;
	pthread_mutex_unlock(&stopMutex);
}

bool Booth::isStopped(){
	return stopped;
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

	while(!thisThread->stop){
		thisThread->queue->addPeople();
		usleep(thisThread->timerMS * 1000);
	}


	thisThread->stopped = true;

	pthread_exit(NULL);
}
