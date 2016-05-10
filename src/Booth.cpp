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
	timerMS = 5000;

	int lines, columns;
	getmaxyx(parent, lines, columns);

	Graphics::createDerWindow(winBooth, parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1);
	Graphics::createBox(winBooth, '#', '#');

	reportStatus();

	pthread_create(&queThread, NULL, &Booth::serve, this);
}

Booth::~Booth(){
	stop = true;

	pthread_join(queThread, NULL);

	Graphics::deleteWindow(winBooth);
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
		usleep(thisThread->timerMS);
	}
}
