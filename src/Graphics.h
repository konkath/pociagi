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
	static void createWindow(WINDOW*& win, int height, int width, int xStart, int yStart);
	static void deleteWindow(WINDOW*& win);

	static void createChildWindow(WINDOW*& win, WINDOW*& parent, int height, int width, int xStart, int yStart);

	static void createBox(WINDOW*& win, chtype vertical, chtype horizontal);
	static void showInMiddle(WINDOW*& win, string txt);
protected:
private:
};



#endif /* GRAPHICS_H_ */
