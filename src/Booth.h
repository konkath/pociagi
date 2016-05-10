/*
 * Booth.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef BOOTH_H_
#define BOOTH_H_

#include <Graphics.h>
#include <Platforms.h>
#include <Queue.h>
#include <unistd.h>

class Booth{
public:
	Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que);
	~Booth();

	void stopBooth();
	bool isStopped();

protected:
private:
	WINDOW* winBooth;
	bool free;
	bool stop;
	bool stopped;

	int timerMS;

	pthread_t queThread;
	pthread_mutex_t stopMutex = PTHREAD_MUTEX_INITIALIZER;

	Platforms* platforms;
	Queue* queue;

	void reportStatus();
	static void* serve(void* me);
};



#endif /* BOOTH_H_ */
