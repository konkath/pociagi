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

	Graphics::createDerWindow(winBooth, parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1);
	Graphics::createBox(winBooth, '#', '#');

	reportStatus();

	pthread_create(&queThread, NULL, &Booth::serve, this);
}

Booth::~Booth(){
	Graphics::deleteWindow(winBooth);

	pthread_join(queThread, NULL);

	delete randomGenerator;
	delete stopMutex;
	pthread_cond_destroy(&stopCond);
}

void Booth::stopBooth(){
	stopMutex->lock();
	stop = true;
	//wait for serve to finish
	pthread_cond_wait(&stopCond, stopMutex->getMutex());
	stopMutex->unlock();
}

void Booth::reportStatus(){
	string str[1];
	if(free){
		str[0] = "W";
		Graphics::showInMiddle(winBooth, str, 1);
	}else{
		str[0] = "Z";
		Graphics::showInMiddle(winBooth, str, 1);
	}
}

void* Booth::serve(void* me){
	Booth* thisThread = static_cast<Booth*>(me);

	bool isStopped = false;

	while(!isStopped){
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
		isStopped = thisThread->stop;
		thisThread->stopMutex->unlock();
	}

	thisThread->stopMutex->lock();
	pthread_cond_signal(&thisThread->stopCond);
	thisThread->stopMutex->unlock();

	pthread_exit(NULL);
}
