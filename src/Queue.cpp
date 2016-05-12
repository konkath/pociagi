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

	peopleMutex = new Mutex();
	stopMutex = new Mutex();
	pthread_cond_init(&stopCond, NULL);

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

	delete peopleMutex;
	delete stopMutex;
	pthread_cond_destroy(&stopCond);
}


void Queue::addPeople(){
	peopleMutex->lock();
	//queueLock();
	people++;
	string str = to_string(people);
	peopleMutex->unlock();

	Graphics::showInMiddle(queWindow, str);
}

void Queue::removePeople(){
	peopleMutex->lock();
	people--;
	string str = to_string(people);
	peopleMutex->unlock();

	Graphics::showInMiddle(queWindow, str);
}

void* Queue::populate(void *me){
	Queue* thisThread = static_cast<Queue*>(me);

	bool isStopped = false;

	while(!isStopped){
		thisThread->addPeople();
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
