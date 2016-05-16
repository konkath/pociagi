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
	static const int maxBooths = 3;
	int nOfBooths;
	bool stop;

	Graphics* winBooths;
	Platforms* platforms;
	Queue* queue;
	Booth* booths[maxBooths];

	pthread_t addBoothThread, rmBoothThread;

	void deleteBooth(int idx);

	static void* boothAdder(void* me);
	static void* boothRemover(void* me);

	void stopThreads();
};


#endif /* BOOTHS_H_ */
