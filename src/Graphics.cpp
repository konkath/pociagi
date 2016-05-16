/*
 * Graphics.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Graphics.h>
#include <iostream>

int Graphics::graphicLock(){
	return pthread_mutex_lock(&graphicMutex);
}

int Graphics::graphicUnlock(){
	return pthread_mutex_unlock(&graphicMutex);
}

WINDOW*& Graphics::getWin(){
	return win;
}

//---------------------------------------------------

Graphics::Graphics(int nLines, int nColumns, int yStart, int xStart,
					chtype vertical, chtype horizontal):vertical(vertical),
					horizontal(horizontal){
	Graphics::graphicLock();

	win = newwin(nLines, nColumns, yStart, xStart);
	touchwin(win);
	wrefresh(win);

	Graphics::graphicUnlock();

	createBox();
}

Graphics::Graphics(WINDOW*& parent, int nLines, int nColumns, int yStart,
					int xStart, chtype vertical, chtype horizontal)
					:vertical(vertical), horizontal(horizontal){
	Graphics::graphicLock();

	win = derwin(parent, nLines, nColumns, yStart, xStart);
	touchwin(win);
	wrefresh(win);

	Graphics::graphicUnlock();

	createBox();
}

Graphics::~Graphics(){
	Graphics::graphicLock();

	//delete border as it likes to stay on screen
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	werase(win);
	wrefresh(win);

	delwin(win);
	win = NULL;
	refresh();

	Graphics::graphicUnlock();

}

void Graphics::createBox(){
	Graphics::graphicLock();

	box(win, vertical, horizontal);
	wrefresh(win);

	Graphics::graphicUnlock();
}

void Graphics::setColor(int color){
	Graphics::graphicLock();

	wbkgd(win, COLOR_PAIR(color));
	wrefresh(win);

	Graphics::graphicUnlock();
}

void Graphics::showInMiddle(string* txt, int nOfElements){
	int row, col;

	Graphics::graphicLock();

	werase(win);
	getmaxyx(win, row, col);
	for (int i = 0; i < nOfElements; ++i){
		mvwaddstr(win,
				(row / 2) - (nOfElements / 2 + i),
				col / 2 - txt[i].length() / 2,
				txt[i].c_str());
	}

	Graphics::graphicUnlock();

	createBox();
}
