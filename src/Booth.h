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

class Booth{
public:
	Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que);
	~Booth();

protected:
private:
	WINDOW* winBooth;
	bool free;
	int timerMS;

	Platforms* platforms;
	Queue* queue;

	void reportStatus();
};



#endif /* BOOTH_H_ */
