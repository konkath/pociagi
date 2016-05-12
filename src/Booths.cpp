/*
 * Booths.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booths.h>
#include <iostream>

Booths::Booths(Platforms* plat, Queue* que):platforms(plat), queue(que){
	nOfBooths = 0;
	booths = new Booth*[maxBooths];

	int lines = LINES * 0.7;
	int columns = COLS * 0.2;
	int orgDistance = COLS * 0.35;

	Graphics::createWindow(winBooths, lines, columns, LINES - lines,
							COLS - orgDistance );
	Graphics::createBox(winBooths, '*', '*');

	//start with single booth open
	addBooth();
}

Booths::~Booths(){
	for(int i = 0; i < nOfBooths; ++i){
		deleteBooth(i);
	}

	delete [] booths;

	Graphics::deleteWindow(winBooths);
}

void Booths::addBooth(){
	if (nOfBooths < maxBooths){
		booths[nOfBooths] = new Booth(nOfBooths, winBooths, platforms, queue);
		nOfBooths++;
	}
}

void Booths::removeBooth(){
	if(1 < nOfBooths){
		nOfBooths--;
		deleteBooth(nOfBooths);
	}
}

void Booths::deleteBooth(int idx){
	booths[idx]->stopBooth();

	delete booths[idx];
	booths[idx] = NULL;
}

