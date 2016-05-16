#include <Graphics.h>
#include <iostream>

//static mutex so every object can lock same mutex
int Graphics::graphicLock(){
	return pthread_mutex_lock(&graphicMutex);
}

//static mutex so every object can unlock same mutex
int Graphics::graphicUnlock(){
	return pthread_mutex_unlock(&graphicMutex);
}

//return reference for window
//(its needed for derwin)
WINDOW*& Graphics::getWin(){
	return win;
}

//create normal window
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

//create children window
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

//delete window
Graphics::~Graphics(){
	Graphics::graphicLock();
	werase(win);
	wrefresh(win);
	delwin(win);
	win = NULL;
	refresh();
	Graphics::graphicUnlock();
}

//create box around window
void Graphics::createBox(){
	Graphics::graphicLock();
	box(win, vertical, horizontal);
	wrefresh(win);
	Graphics::graphicUnlock();
}

//set window background color
void Graphics::setColor(int color){
	Graphics::graphicLock();
	wbkgd(win, COLOR_PAIR(color));
	wrefresh(win);
	Graphics::graphicUnlock();
}

//show text in middle of the window
void Graphics::showInMiddle(string* txt, int nOfElements){
	int row, col;

	Graphics::graphicLock();
	werase(win);
	getmaxyx(win, row, col);

	//every element of txt array will be displayed in different line
	for (int i = 0; i < nOfElements; ++i){
		mvwaddstr(win, (row / 2) - (nOfElements / 2 + i),
				col / 2 - txt[i].length() / 2, txt[i].c_str());
	}

	Graphics::graphicUnlock();

	createBox();
}
