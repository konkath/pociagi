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

	stop = false;
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
	stopThreads();

	pthread_join(addBoothThread, NULL);
	pthread_join(rmBoothThread, NULL);

	for(int i = 0; i < nOfBooths; ++i){
		deleteBooth(i);
	}

	Graphics::deleteWindow(winBooths);
}

void Booths::addBooth(){
	queue->boothsMutex->lock();

	if (nOfBooths < maxBooths){
		booths[nOfBooths] = new Booth(nOfBooths, winBooths, platforms, queue);
		nOfBooths++;
	}

	queue->boothsMutex->unlock();
}

void Booths::removeBooth(){
	queue->boothsMutex->lock();

	if(1 < nOfBooths){
		nOfBooths--;
		deleteBooth(nOfBooths);
	}

	queue->boothsMutex->unlock();
}

void Booths::deleteBooth(int idx){
	//no need for mutex as it is held in removeBooth method
	booths[idx]->stopBooth();
	delete booths[idx];
	booths[idx] = NULL;
}

void* Booths::boothAdder(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	thisThread->queue->boothsMutex->lock();
	while(!thisThread->stop){
		pthread_cond_wait(&thisThread->queue->addCond,
				thisThread->queue->boothsMutex->getMutex());

		thisThread->queue->boothsMutex->unlock();
		thisThread->addBooth();
		thisThread->queue->boothsMutex->lock();
	}//exit locked
	thisThread->queue->boothsMutex->unlock();

	pthread_exit(NULL);
}

void* Booths::boothRemover(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	thisThread->queue->boothsMutex->lock();
	while(!thisThread->stop){
		pthread_cond_wait(&thisThread->queue->rmCond,
				thisThread->queue->boothsMutex->getMutex());

		thisThread->queue->boothsMutex->unlock();
		thisThread->removeBooth();
		thisThread->queue->boothsMutex->lock();
	}//exit locked
	thisThread->queue->boothsMutex->unlock();

	pthread_exit(NULL);
}

void Booths::stopThreads(){
	queue->boothsMutex->lock();
	stop = true;
	pthread_cond_signal(&queue->addCond);
	pthread_cond_signal(&queue->rmCond);
	queue->boothsMutex->unlock();
}
