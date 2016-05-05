/*
 * Booths.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booths.h>

Booths::Booths(){
	nOfBooths = 0;
	booths = new Booth*[maxBooths];

	Graphics::createWindow(winBooths, 25, 15, COLS - 40, LINES - 10);
	Graphics::createBox(winBooths, '*', '*');
}

Booths::~Booths(){
	Graphics::deleteWindow(winBooths);
	delete booths;
}

void Booths::addBooth(){
	if (nOfBooths < maxBooths){
		booths[nOfBooths] = new Booth(nOfBooths, winBooths);
		nOfBooths++;
	}
}

void Booths::removeBooth(){
	if(1 < nOfBooths){
		delete booths[nOfBooths];
		booths[nOfBooths] = NULL;
		nOfBooths--;
	}
}

