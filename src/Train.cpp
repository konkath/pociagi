/*
 * Train.cpp
 *
 *  Created on: 8 maj 2016
 *      Author: user
 */

#include <Train.h>

Train::Train(int platform, int id){
	freeSeats = 30;
	passengersOut = 0;

	timeoutMS = 500;

	int lines = LINES * 0.5;
	int columns = COLS * 0.08;

	//TODO ustalic orgDistance na podstawie platform i id
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
}

//TODO konstruktor losowego pociagu
Train::Train(int platform, int id, int passengersOut, int freeSeats)
		:passengersOut(passengersOut), freeSeats(freeSeats){
	timeoutMS = 500;

}

Train::~Train(){
	Graphics::deleteWindow(winTrain);
}


