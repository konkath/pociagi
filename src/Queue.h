/*
 * Queu.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <curses.h>
#include <Graphics.h>
#include <pthread.h>
#include <string>
using namespace std;

class Queue{
public:
	Queue();
	~Queue();

	void addPeople();
	void removePeople();
protected:
private:
	WINDOW* queWindow;
	int timerMS;
	int people;
	bool stop;

	pthread_t queueThread;
	pthread_mutex_t peopleMutex;
	pthread_mutex_t stopMutex;
	pthread_cond_t stopCond;

	int queueLock();
	int queueUnlock();
	int stopLock();
	int stopUnlock();

	static void* populate(void* me);
};



#endif /* QUEUE_H_ */
