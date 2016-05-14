/*
 * RandomGenerator.h
 *
 *  Created on: 12 maj 2016
 *      Author: user
 */

#ifndef SRC_RANDOMGENERATOR_H_
#define SRC_RANDOMGENERATOR_H_

#include <random>
#include <Mutex.h>
using namespace std;

class RandomGenerator{
public:
	RandomGenerator();
	~RandomGenerator();

	int getRandomInt(int begin, int end);
protected:
private:
	random_device rd;
	mt19937 generate;
	Mutex* randomMutex;
};



#endif /* SRC_RANDOMGENERATOR_H_ */
