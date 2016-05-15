/*
 * Booths.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef BOOTHS_H_
#define BOOTHS_H_

#include <Graphics.h>
#include <Booth.h>

class Booths{
public:
	Booths(Platforms* plat, Queue* que);
	~Booths();

	void addBooth();
	void removeBooth();

protected:
private:
	WINDOW* winBooths;
	static const int maxBooths = 3;
	int nOfBooths;
	bool stop;

	Booth* booths[maxBooths];
	Platforms* platforms;
	Queue* queue;

	pthread_t addBoothThread, rmBoothThread;

	void deleteBooth(int idx);

	static void* boothAdder(void* me);
	static void* boothRemover(void* me);

	void waitForCond(pthread_cond_t cond);
	void stopThreads();
};


#endif /* BOOTHS_H_ */
