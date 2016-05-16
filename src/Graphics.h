#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <curses.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <Mutex.h>
using namespace std;

static pthread_mutex_t graphicMutex;

class Graphics{
public:
	Graphics(int nLines, int nColumns, int yStart, int xStart,
			chtype vertical, chtype horizontal);
	Graphics(WINDOW*& win, int nLines, int nColumns, int yStart, int xStart,
			chtype vertical, chtype horizontal);
	~Graphics();

	static int graphicLock();
	static int graphicUnlock();

	void setColor(int color);
	void showInMiddle(string* txt, int nOfElements);

	WINDOW*& getWin();

protected:
private:
	WINDOW* win;
	chtype vertical, horizontal;

	void createBox();
};



#endif /* GRAPHICS_H_ */
