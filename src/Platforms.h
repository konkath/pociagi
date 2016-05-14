/*
 * Platforms.h
 *
 *  Created on: 7 maj 2016
 *      Author: user
 */

#ifndef SRC_PLATFORMS_H_
#define SRC_PLATFORMS_H_

#include <Graphics.h>
#include <Train.h>
#include <vector>
#include <SignalLight.h>
#include <RandomGenerator.h>
#include <Mutex.h>

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
	vector<int>* people;
	Train** trains;
	SignalLight* signalLight;
	RandomGenerator* randomGenerator;
	Mutex* peopleMutex, *tempMutex;

	void addRandomTrain(int idx);

	int getPlatform(int idx);
	int getId(int idx);

	int getTicketOwners(int platform, int id);

	void reportStatus(int idx);

};


#endif /* SRC_PLATFORMS_H_ */
