/*
 * Graphics.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Graphics.h>
#include <iostream>

void Graphics::createWindow(WINDOW*& win, int nLines, int nColumns, int yStart, int xStart){
	win = newwin(nLines, nColumns, yStart, xStart);
	touchwin(win);
	refreshWin(win);
}

void Graphics::createDerWindow(WINDOW*& win, WINDOW*& parent,
		int nLines, int nColumns, int yStart, int xStart){

	win = derwin(parent, nLines, nColumns, yStart, xStart);
	touchwin(win);
	refreshWin(win);
}


void Graphics::deleteWindow(WINDOW*& win){
	//delete border as it likes to stay on screen
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	werase(win);
	refreshWin(win);

	delwin(win);

	pthread_mutex_lock(&graphicMutex);
	refresh();
	pthread_mutex_unlock(&graphicMutex);
}

void Graphics::createBox(WINDOW*& win, chtype vertical, chtype horizontal){
	box(win, vertical, horizontal);

	refreshWin(win);
}

void Graphics::setColor(WINDOW*& win, int color){
	wbkgd(win, COLOR_PAIR(color));
	refreshWin(win);
}

void Graphics::showInMiddle(WINDOW*& win, string txt){
	int row, col;
	getmaxyx(win, row, col);

	mvwaddstr(win, row / 2, col / 2 - txt.length() / 2, txt.c_str());

	refreshWin(win);
}


void Graphics::showOnTop(WINDOW*& win, string txt){
	int col = getmaxx(win);

	mvwaddstr(win, 2, col / 2 - txt.length() / 2, txt.c_str());

	refreshWin(win);
}

void Graphics::showOnBottom(WINDOW*& win, string txt){
	int row, col;
	getmaxyx(win, row, col);

	mvwaddstr(win, row - 2, col / 2 - txt.length() / 2, txt.c_str());

	refreshWin(win);
}

void Graphics::refreshWin(WINDOW*& win){
	pthread_mutex_lock(&graphicMutex);
	wrefresh(win);
	pthread_mutex_unlock(&graphicMutex);
}
