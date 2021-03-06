#ifndef SRC_PLATFORMS_H_
#define SRC_PLATFORMS_H_

#include <Graphics.h>
#include <Train.h>
#include <vector>
#include <SignalLight.h>
#include <Queue.h>
#include <RandomGenerator.h>
#include <Mutex.h>

class Train;

class Platforms{
public:
	Platforms(SignalLight* signal, Queue* queue);
	~Platforms();

	void addTrain(int idx);
	void removeTrain(int idx);

	void addPeople(int idx);
	bool removePeople(int idx);

	int getPlatform(int idx);
	int getId(int idx);

protected:
private:
	static const int nOfPlatforms = 2;
	static const int nOfTrains = 4;
	Graphics* winPlatform[nOfPlatforms];
	vector<int> people[nOfPlatforms];
	Train* trains[nOfTrains];
	SignalLight* signalLight;
	Queue* queue;
	RandomGenerator* randomGenerator;

	Mutex *peopleMutex, *trainMutex;
	pthread_t trainThread;
	pthread_t trainRmThread;

	int timerMS;
	bool stop;
	bool addRandomTrain(int idx);

	int getTicketOwners(int platform, int id);

	void reportStatus(int idx);

	static void* trainAdder(void* me);
	static void* trainRemover(void* me);
};


#endif /* SRC_PLATFORMS_H_ */
