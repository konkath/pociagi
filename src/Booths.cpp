/*
 * Booths.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booths.h>
#include <iostream>

Booths::Booths(){
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
	Graphics::deleteWindow(winBooths);

	for(int i = 0; i < nOfBooths; ++i){
		delete booths[i];
	}

	delete [] booths;
}

void Booths::addBooth(){
	if (nOfBooths < maxBooths){
		booths[nOfBooths] = new Booth(nOfBooths);
		nOfBooths++;
	}
}

void Booths::removeBooth(){
	if(1 < nOfBooths){
		nOfBooths--;
		delete booths[nOfBooths];
		booths[nOfBooths] = NULL;
	}
}

