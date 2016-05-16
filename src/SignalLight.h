/*
 * SignalLight.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef SIGNALLIGHT_H_
#define SIGNALLIGHT_H_

#include <Graphics.h>
#include <Mutex.h>

class SignalLight{
public:
	SignalLight();
	~SignalLight();

	void changeColor();
	bool isGreen();

	pthread_cond_t lightCond;
	Mutex *lightMutex;

protected:
private:
	Graphics* winSignal;
	bool greenLight, stop;
	int redTimer, greenTimer;

	pthread_t lightThread;
	Mutex *stopMutex;

	void setGreen();
	void setRed();

	static void* lightChanger(void* me);
};



#endif /* SIGNALLIGHT_H_ */
