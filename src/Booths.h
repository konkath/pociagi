/*
 * Booths.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef BOOTHS_H_
#define BOOTHS_H_

#include <Graphics.h>
#include <Booth.h>

class Booths{
public:
	Booths(Platforms* plat, Queue* que);
	~Booths();

	void addBooth();
	void removeBooth();

protected:
private:
	WINDOW* winBooths;
	const int maxBooths = 3;
	int nOfBooths;

	Booth** booths;
	Platforms* platforms;
	Queue* queue;

	void deleteBooth(int idx);
};


#endif /* BOOTHS_H_ */
