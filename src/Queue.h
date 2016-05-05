/*
 * Queu.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <curses.h>
#include <Graphics.h>
#include <string>
using namespace std;

class Queue{
public:
	Queue();
	~Queue();

	void addPeople();
	void removePeople();
protected:
private:
	WINDOW* queWindow;
	int people;
};



#endif /* QUEUE_H_ */
