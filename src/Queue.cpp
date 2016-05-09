/*
 * Queue.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Queue.h>

Queue::Queue(){
	people = 0;
	int lines = LINES * 0.7;
	int columns = COLS * 0.15;

	Graphics::createWindow(queWindow, lines, columns, LINES - lines,
							COLS - columns);
	Graphics::createBox(queWindow, '$', '$');
}

Queue::~Queue(){
	Graphics::deleteWindow(queWindow);
}


void Queue::addPeople(){
	people++;

	Graphics::showInMiddle(queWindow, to_string(people));
}

void Queue::removePeople(){
	people--;

	Graphics::showInMiddle(queWindow, to_string(people));
}
