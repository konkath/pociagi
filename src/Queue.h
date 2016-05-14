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

	bool isEmpty();

	pthread_cond_t addCond, rmCond;
	Mutex* boothsMutex;
protected:
private:
	WINDOW* queWindow;
	int timerMS;
	int people;
	const int add = 20, rm = 10;
	bool stop;

	pthread_t queueThread;

	Mutex* peopleMutex;
	Mutex* stopMutex;
	pthread_cond_t stopCond;

	static void* populate(void* me);
};



#endif /* QUEUE_H_ */
