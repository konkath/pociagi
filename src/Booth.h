#ifndef BOOTH_H_
#define BOOTH_H_

#include <Graphics.h>
#include <Platforms.h>
#include <Queue.h>
#include <RandomGenerator.h>

class Booth{
public:
	Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que);
	~Booth();

	void stopBooth();
protected:
private:
	bool free;
	bool stop;
	int timerMS;

	pthread_t queThread;
	Mutex* stopMutex;

	Graphics* winBooth;
	Platforms* platforms;
	Queue* queue;
	RandomGenerator* randomGenerator;

	void reportStatus();
	static void* serve(void* me);
};

#endif /* BOOTH_H_ */
