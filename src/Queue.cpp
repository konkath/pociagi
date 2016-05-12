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

	int lines = LINES * 0.7;
	int columns = COLS * 0.15;

	pthread_mutex_init(&peopleMutex, NULL);
	pthread_mutex_init(&stopMutex, NULL);
	pthread_cond_init(&stopCond, NULL);

	Graphics::createWindow(queWindow, lines, columns, LINES - lines,
							COLS - columns);
	Graphics::createBox(queWindow, '$', '$');

	pthread_create(&queueThread, NULL, &Queue::populate, this);
}

Queue::~Queue(){
	stopLock();
	printf("lock na stop");
	stop = true;
	//wait for populate to finish

	printf("czekam na cond");
	pthread_cond_wait(&stopCond, &stopMutex);
	printf("mam cond");
	stopUnlock();

	printf("idzie delete");

	Graphics::deleteWindow(queWindow);

	pthread_mutex_destroy(&peopleMutex);
	pthread_mutex_destroy(&stopMutex);
	pthread_cond_destroy(&stopCond);
}


void Queue::addPeople(){
	queueLock();
	people++;
	string str = to_string(people);
	queueUnlock();

	Graphics::showInMiddle(queWindow, str);
}

void Queue::removePeople(){
	queueLock();
	people--;
	string str = to_string(people);
	queueUnlock();

	Graphics::showInMiddle(queWindow, str);
}

int Queue::queueLock(){
	return pthread_mutex_lock(&peopleMutex);
}

int Queue::queueUnlock(){
	return pthread_mutex_unlock(&peopleMutex);
}

void* Queue::populate(void *me){
	Queue* thisThread = static_cast<Queue*>(me);

	bool isStopped = false;

	while(!isStopped){
		thisThread->addPeople();
		usleep(thisThread->timerMS * 1000);

		thisThread->stopLock();
		isStopped = thisThread->stop;
		thisThread->stopUnlock();
	}

	thisThread->stopLock();
	printf("signal na cond");
	pthread_cond_signal(&thisThread->stopCond);
	printf("po signale na cond");
	thisThread->stopUnlock();

	pthread_exit(NULL);
}


int Queue::stopLock(){
	return pthread_mutex_lock(&stopMutex);
}

int Queue::stopUnlock(){
	return pthread_mutex_unlock(&stopMutex);
}
