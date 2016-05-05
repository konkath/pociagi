/*
 * Queue.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Queue.h>

Queue::Queue(){
	Graphics::createWindow(queWindow, 10, 10, LINES - 10, COLS - 10);
	Graphics::createBox(queWindow, '$', '$');
	people = 0;
}

Queue::~Queue(){
	Graphics::deleteWindow(queWindow);
}


void Queue::addPeople(){
	people++;

	//tu nie ma bledu
	Graphics::showInMiddle(queWindow, to_string(people));
}

void Queue::removePeople(){
	people--;
	Graphics::showInMiddle(queWindow, to_string(people));
}
