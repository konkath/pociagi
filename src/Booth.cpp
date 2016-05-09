/*
 * Booth.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booth.h>
#include <iostream>

Booth::Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que)
			:platforms(plat), queue(que){
	free = true;
	timerMS = 500;

	int lines, columns;
	getmaxyx(parent, lines, columns);

	Graphics::createDerWindow(winBooth, parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1);
	Graphics::createBox(winBooth, '#', '#');

	reportStatus();
}

Booth::~Booth(){
	Graphics::deleteWindow(winBooth);
}

void Booth::reportStatus(){
	if(free){
		Graphics::showInMiddle(winBooth, "W");
	}else{
		Graphics::showInMiddle(winBooth, "Z");
	}
}
