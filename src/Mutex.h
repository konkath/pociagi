/*
 * Mutex.h
 *
 *  Created on: 12 maj 2016
 *      Author: user
 */

#ifndef SRC_MUTEX_H_
#define SRC_MUTEX_H_

#include <pthread.h>

class Mutex{
public:
	Mutex();
	~Mutex();

	int lock();
	int unlock();

	pthread_mutex_t* getMutex();

protected:
private:
	pthread_mutex_t mutex;
};



#endif /* SRC_MUTEX_H_ */
