/*
 * Booth.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef BOOTH_H_
#define BOOTH_H_

#include <Graphics.h>

class Booth{
public:
	Booth(int id, WINDOW*& parent);
	~Booth();

	void reportStatus();
protected:
private:
	int id;
	WINDOW* winBooth;
	bool free;
	int timerMS;
};



#endif /* BOOTH_H_ */
