/*
 * Platforms.h
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#ifndef SRC_PLATFORMS_H_
#define SRC_PLATFORMS_H_

#include <curses.h>
#include <Graphics.h>
#include <Train.h>
#include <queue>
#include <SignalLight.h>


class Platforms{
public:
	Platforms(SignalLight* signal);
	~Platforms();

	void addTrain(int idx);
	void removeTrain(int idx);

	void addPeople(int idx);
	bool removePeople(int idx);

protected:
private:
	const int nOfPlatforms = 2;
	const int nOfTrains = 4;
	WINDOW** winPlatform;
	deque<int>* people;
	Train** trains;
	SignalLight* signalLight;

	void addRandomTrain();

	int getPlatform(int idx);
	int getId(int idx);

	void reportStatus();
};


#endif /* SRC_PLATFORMS_H_ */
