/*
 * Queue.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Queue.h>

Queue::Queue(){
	people = 0;
	stop = false;
	timerMS = 200;

	peopleMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	stopMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	boothsMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);

	pthread_cond_init(&stopCond, NULL);
	pthread_cond_init(&addCond, NULL);
	pthread_cond_init(&rmCond, NULL);

	int lines = LINES * 0.7;
	int columns = COLS * 0.15;

	Graphics::createWindow(queWindow, lines, columns, LINES - lines,
							COLS - columns);
	Graphics::createBox(queWindow, '$', '$');

	pthread_create(&queueThread, NULL, &Queue::populate, this);
}

Queue::~Queue(){
	stopMutex->lock();
	stop = true;
	//wait for populate to finish
	pthread_cond_wait(&stopCond, stopMutex->getMutex());
	stopMutex->unlock();

	Graphics::deleteWindow(queWindow);

	pthread_join(queueThread, NULL);

	delete boothsMutex;
	delete peopleMutex;
	delete stopMutex;
	pthread_cond_destroy(&stopCond);
	pthread_cond_destroy(&addCond);
	pthread_cond_destroy(&rmCond);
}

void Queue::addPeople(){
	peopleMutex->lock();
	//queueLock();
	people++;
	string str[1] = to_string(people);

	if(people == add){
		boothsMutex->lock();
		pthread_cond_signal(&addCond);
		boothsMutex->unlock();
	}
	peopleMutex->unlock();

	Graphics::showInMiddle(queWindow, str, 1);
}

void Queue::removePeople(){
	peopleMutex->lock();
	people--;
	string str[1] = to_string(people);

	if(people == rm){
		boothsMutex->lock();
		pthread_cond_signal(&rmCond);
		boothsMutex->unlock();
	}

	peopleMutex->unlock();

	Graphics::showInMiddle(queWindow, str, 1);
}

bool Queue::isEmpty(){
	peopleMutex->lock();
	bool result = people > 0 ? true : false;
	peopleMutex->unlock();

	return result;
}

void* Queue::populate(void *me){
	Queue* thisThread = static_cast<Queue*>(me);

	thisThread->stopMutex->lock();
	while(!thisThread->stop){
		thisThread->stopMutex->unlock();

		thisThread->addPeople();
		usleep(thisThread->timerMS * 1000);

		thisThread->stopMutex->lock();
	}//exit locked

	pthread_cond_signal(&thisThread->stopCond);
	thisThread->stopMutex->unlock();

	pthread_exit(NULL);
}
