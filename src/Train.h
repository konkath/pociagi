/*
 * Train.h
 *
 *  Created on: 8 maj 2016
 *      Author: user
 */

#ifndef SRC_TRAIN_H_
#define SRC_TRAIN_H_

#include <Graphics.h>
#include <SignalLight.h>
#include <Queue.h>
#include <Platforms.h>

class Platforms;

class Train{
public:
	Train(SignalLight* signal, Platforms* platforms, Queue* queue, int idx);
	Train(SignalLight* signal, Platforms* platforms, Queue* queue, int idx,
			int passengersOut, int freeSeats);
	~Train();

	void sendStop();

	bool isReady();

protected:
private:
	WINDOW* winTrain;
	SignalLight* signalLight;
	Platforms* platforms;
	Queue* queue;

	int idx;
	int freeSeats, passengersOut;
	int timeoutMS;
	bool stop;
	string status;

	Mutex *passengersMutex, *seatsMutex, *statusMutex, *stopMutex;
	pthread_t trainThread;

	void initThread();
	void initGraphic(int idx);

	void reportPassengers();

	static void* conductor(void* me);

};


#endif /* SRC_TRAIN_H_ */
