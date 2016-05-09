/*
 * Train.cpp
 *
 *  Created on: 8 maj 2016
 *      Author: user
 */

#include <Train.h>

Train::Train(SignalLight* signal, int platform, int id):signalLight(signal){
	freeSeats = 30;
	passengersOut = 0;

	timeoutMS = 500;

	int lines = LINES * 0.5;
	int columns = COLS * 0.08;

	int orgDistance = COLS * 0.48;

	if (1 == platform){
		orgDistance += COLS * 0.30;
	}

	if (1 == id){
		orgDistance += COLS * 0.2;
	}

	Graphics::createWindow(winTrain, lines, columns,
							LINES - lines, COLS - orgDistance );
	Graphics::createBox(winTrain, '8', '!');

	reportPassengers();
}

//konstruktor losowego pociagu
Train::Train(SignalLight* signal, int platform, int id, int passengersOut,
		int freeSeats):signalLight(signal), freeSeats(freeSeats),
		passengersOut(passengersOut){
	timeoutMS = 500;

	int lines = LINES * 0.5;
	int columns = COLS * 0.08;

	int orgDistance = COLS * 0.48;

	if (1 == platform){
		orgDistance += COLS * 0.30;
	}

	if (1 == id){
		orgDistance += COLS * 0.2;
	}

	Graphics::createWindow(winTrain, lines, columns,
							LINES - lines, COLS - orgDistance );
	Graphics::createBox(winTrain, '8', '!');
	reportPassengers();
}

Train::~Train(){
	Graphics::deleteWindow(winTrain);
}

void Train::reportPassengers(){
	//wysiadajacy
	Graphics::showOnTop(winTrain, "wy: " + to_string(passengersOut));
	//wolne miejsca
	Graphics::showInMiddle(winTrain, "wo: " + to_string(freeSeats));
}


