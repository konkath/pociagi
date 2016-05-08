/*
 * Platforms.h
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#ifndef SRC_PLATFORMS_H_
#define SRC_PLATFORMS_H_

#include <curses.h>
#include <Graphics.h>

class Platforms{
public:
	Platforms();
	~Platforms();
protected:
private:
	const int nOfPlatforms = 2;
	WINDOW** winPlatform;
	int* people;
};


#endif /* SRC_PLATFORMS_H_ */
