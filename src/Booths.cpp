/*
 * Booths.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booths.h>
#include <iostream>

Booths::Booths(Platforms* plat, Queue* que):platforms(plat), queue(que){
	nOfBooths = 0;
	booths = new Booth*[maxBooths];
	boothsMutex = new Mutex(PTHREAD_MUTEX_RECURSIVE);

	int lines = LINES * 0.7;
	int columns = COLS * 0.2;
	int orgDistance = COLS * 0.35;

	Graphics::createWindow(winBooths, lines, columns, LINES - lines,
							COLS - orgDistance );
	Graphics::createBox(winBooths, '*', '*');

	//start with single booth open
	addBooth();

	pthread_create(&addBoothThread, NULL, &Booths::boothAdder, this);
	pthread_create(&rmBoothThread, NULL, &Booths::boothRemover, this);
}

Booths::~Booths(){
	pthread_cancel(addBoothThread);
	pthread_cancel(rmBoothThread);

	pthread_join(addBoothThread, NULL);
	pthread_join(rmBoothThread, NULL);

	for(int i = 0; i < nOfBooths; ++i){
		deleteBooth(i);
	}

	delete [] booths;
	delete boothsMutex;

	Graphics::deleteWindow(winBooths);
}

void Booths::addBooth(){
	if (nOfBooths < maxBooths){
		booths[nOfBooths] = new Booth(nOfBooths, winBooths, platforms, queue);
		nOfBooths++;
	}
}

void Booths::removeBooth(){
	boothsMutex->lock();

	if(1 < nOfBooths){
		nOfBooths--;
		deleteBooth(nOfBooths);
	}

	boothsMutex->unlock();
}

void Booths::deleteBooth(int idx){
	boothsMutex->lock();

	booths[idx]->stopBooth();
	delete booths[idx];
	booths[idx] = NULL;

	boothsMutex->unlock();
}

void* Booths::boothAdder(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	while(true){
		thisThread->boothsMutex->lock();
		pthread_cond_wait(&thisThread->queue->addCond,
				thisThread->boothsMutex->getMutex());
		thisThread->addBooth();
		thisThread->boothsMutex->unlock();
	}
}

void* Booths::boothRemover(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	while(true){
		thisThread->boothsMutex->lock();
		pthread_cond_wait(&thisThread->queue->rmCond,
				thisThread->boothsMutex->getMutex());
		thisThread->removeBooth();
		thisThread->boothsMutex->unlock();
	}
}

