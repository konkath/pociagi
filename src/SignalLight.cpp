/*
 * SignalLight.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include <SignalLight.h>

SignalLight::SignalLight(){
	greenLight = false;

	int lines = LINES * 0.1;
	int columns = COLS * 0.6;

	Graphics::createWindow(winSignal, lines, columns, 2, 2);
	Graphics::createBox(winSignal, '+', '+');
	Graphics::setColor(winSignal, 1);
}

SignalLight::~SignalLight(){
	Graphics::deleteWindow(winSignal);
}

void SignalLight::changeColor(){
	greenLight = !greenLight;

	if(greenLight){
		Graphics::setColor(winSignal, 2);
	}else{
		Graphics::setColor(winSignal, 1);
	}
}


