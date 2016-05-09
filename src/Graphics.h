/*
 * Graphics.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <curses.h>
#include <string>
using namespace std;

class Graphics{
public:
	static void createWindow(WINDOW*& win, int nLines, int nColumns, int yStart, int xStart);
	static void createDerWindow(WINDOW*& win, WINDOW*& parent, int nLines, int nColumns, int yStart, int xStart);
	static void deleteWindow(WINDOW*& win);

	static void createBox(WINDOW*& win, chtype vertical, chtype horizontal);
	static void setColor(WINDOW*& win, int color);

	static void showInMiddle(WINDOW*& win, string txt);
	static void showOnTop(WINDOW*& win, string txt);
	static void showOnBottom(WINDOW*& win, string txt);
protected:
private:
};



#endif /* GRAPHICS_H_ */
