/*
 * Graphics.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include <Graphics.h>
#include <iostream>

void Graphics::createWindow(WINDOW*& win, int nLines, int nColumns,
		int yStart, int xStart){

	Graphics::graphicLock();

	win = newwin(nLines, nColumns, yStart, xStart);
	touchwin(win);
	wrefresh(win);

	Graphics::graphicUnlock();
}

void Graphics::createDerWindow(WINDOW*& win, WINDOW*& parent,
		int nLines, int nColumns, int yStart, int xStart){

	Graphics::graphicLock();

	win = derwin(parent, nLines, nColumns, yStart, xStart);
	touchwin(win);
	wrefresh(win);

	Graphics::graphicUnlock();
}


void Graphics::deleteWindow(WINDOW*& win){
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

void Graphics::createBox(WINDOW*& win, chtype vertical, chtype horizontal){
	Graphics::graphicLock();

	if (NULL != win){
		box(win, vertical, horizontal);
		wrefresh(win);
	}

	Graphics::graphicUnlock();
}

void Graphics::setColor(WINDOW*& win, int color){
	Graphics::graphicLock();

	if (NULL != win){
		wbkgd(win, COLOR_PAIR(color));
		wrefresh(win);
	}

	Graphics::graphicUnlock();
}

void Graphics::showInMiddle(WINDOW*& win, string* txt, int nOfElements){
	int row, col;

	Graphics::graphicLock();

	if (NULL != win){
		printf("o ja jebie\n");
		getmaxyx(win, row, col);
		printf("o muj borze\n");
		for (int i = 0; i < nOfElements; ++i){
			printf("idz w chuj\n");
			mvwaddstr(win,
					(row / 2) - (nOfElements / 2 + i),
					col / 2 - txt[i].length() / 2,
					"a");
			printf("u woot m8?\n");
			wrefresh(win);
			printf("lel\n");
		}
	}

	Graphics::graphicUnlock();
}

int Graphics::graphicLock(){
	return pthread_mutex_lock(&graphicMutex);
}

int Graphics::graphicUnlock(){
	return pthread_mutex_unlock(&graphicMutex);
}
