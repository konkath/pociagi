/*
 * Booth.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booth.h>
#include <iostream>

	Booth::Booth(int id){
		free = true;
		timerMS = 500;

		int lines = LINES * 0.20;
		int parentLines = LINES * 0.65;
		int columns = COLS * 0.18;
		int orgDistance = COLS * 0.33;

		Graphics::createWindow(winBooth, lines, columns,
								(LINES - parentLines) + (lines * id),
								COLS - orgDistance);
		Graphics::createBox(winBooth, '#', '#');
	}

	Booth::~Booth(){
		Graphics::deleteWindow(winBooth);
	}

	void Booth::reportStatus(){
		if(free)
			Graphics::showInMiddle(winBooth, "W");
		else
			Graphics::showInMiddle(winBooth, "Z");
	}
