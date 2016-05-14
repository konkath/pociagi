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
#include <RandomGenerator.h>

class Booth{
public:
	Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que);
	~Booth();

	void stopBooth();
protected:
private:
	WINDOW* winBooth;
	bool free;
	bool stop;

	int timerMS;

	pthread_t queThread;
	Mutex* stopMutex;
	pthread_cond_t stopCond;

	Platforms* platforms;
	Queue* queue;
	RandomGenerator* randomGenerator;

	void reportStatus();
	static void* serve(void* me);
};

#endif /* BOOTH_H_ */
