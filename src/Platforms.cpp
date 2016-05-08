/*
 * Platforms.cpp
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#include <Platforms.h>

Platforms::Platforms(){
	winPlatform = new WINDOW*[nOfPlatforms];
	people = new int[nOfPlatforms];

	int lines = LINES * 0.5;
	int columns = COLS * 0.1;
	int orgDistance = COLS * 0.6;
	int distance = COLS * 0.30;

	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::createWindow(winPlatform[i], lines, columns, LINES - lines,
								(COLS - orgDistance) - (i * distance));
		Graphics::createBox(winPlatform[i], '|', '-');

		people[i] = 0;
	}
}

Platforms::~Platforms(){
	for(int i = 0; i < nOfPlatforms; ++i){
		Graphics::deleteWindow(winPlatform[i]);
		//delete winPlatform[i];
	}

	delete [] winPlatform;
	delete [] people;
}
