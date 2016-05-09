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

class Train{
public:
	Train(SignalLight* signal, int platform, int id);
	Train(SignalLight* signal, int platform, int id, int passengersOut, int freeSeats);
	~Train();
protected:
private:
	WINDOW* winTrain;
	SignalLight* signalLight;
	int freeSeats;
	int passengersOut;

	int timeoutMS;

	void reportPassengers();
};


#endif /* SRC_TRAIN_H_ */
