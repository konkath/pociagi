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
	Mutex(int type);
	~Mutex();

	int lock();
	int unlock();

	pthread_mutex_t* getMutex();

protected:
private:
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;
};



#endif /* SRC_MUTEX_H_ */
