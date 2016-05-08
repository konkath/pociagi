/*
 * Train.h
 *
 *  Created on: 8 maj 2016
 *      Author: user
 */

#ifndef SRC_TRAIN_H_
#define SRC_TRAIN_H_

#include <Graphics.h>

class Train{
public:
	Train(int platform, int id);
	Train(int platform, int id, int passengersOut, int freeSeats);
	~Train();
protected:
private:
	WINDOW* winTrain;
	int freeSeats;
	int passengersOut;

	int timeoutMS;
};


#endif /* SRC_TRAIN_H_ */
