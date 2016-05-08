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
	Booth(int id);
	~Booth();

protected:
private:
	WINDOW* winBooth;
	bool free;
	int timerMS;

	void reportStatus();
};



#endif /* BOOTH_H_ */
