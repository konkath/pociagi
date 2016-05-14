/*
 * SignalLight.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef SIGNALLIGHT_H_
#define SIGNALLIGHT_H_

#include <Graphics.h>

class SignalLight{
public:
	SignalLight();
	~SignalLight();

	void changeColor();
protected:
private:
	WINDOW* winSignal;
	bool greenLight;
};



#endif /* SIGNALLIGHT_H_ */
