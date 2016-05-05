/*
 * Graphics.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Graphics.h>
#include <iostream>

void Graphics::createWindow(WINDOW*& win, int height, int width, int xStart, int yStart){
	win = newwin(height, width, xStart, yStart);
	touchwin(win);
	wrefresh(win);
}

void Graphics::createChildWindow(WINDOW*& win, WINDOW*& parent, int height, int width, int xStart, int yStart){
	win = derwin(parent, height, width, xStart, yStart);
	touchwin(win);
	wrefresh(win);
}

void Graphics::deleteWindow(WINDOW*& win){
	delwin(win);
	refresh();
}

void Graphics::createBox(WINDOW*& win, chtype vertical, chtype horizontal){
	box(win, vertical, horizontal);
	wrefresh(win);
}

void Graphics::showInMiddle(WINDOW*& win, string txt){
	int row, col;
	getmaxyx(win, row, col);

	mvwaddstr(win, row/2, col/2, txt.c_str());

	wrefresh(win);
}
