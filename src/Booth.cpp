/*
 * Booth.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Booth.h>


	Booth::Booth(int id, WINDOW*& parent):id(id){
		free = true;
		timerMS = 500;

		//TODO zle podawana parametry sa
		// (parent, nlines, ncols, begin_y, begin_x)
		Graphics::createChildWindow(winBooth, parent, 0, 0, COLS, LINES);
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
