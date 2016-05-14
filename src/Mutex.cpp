/*
 * Mutex.cpp
 *
 *  Created on: 12 maj 2016
 *      Author: user
 */

#include <Mutex.h>

Mutex::Mutex(int type){
	pthread_mutexattr_init(&attr);

	if (type == PTHREAD_MUTEX_RECURSIVE){
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	}else{
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
	}

	pthread_mutex_init(&mutex, &attr);
}

Mutex::~Mutex(){
	pthread_mutex_destroy(&mutex);
	pthread_mutexattr_destroy(&attr);
}

int Mutex::lock(){
	return pthread_mutex_lock(&mutex);
}

int Mutex::unlock(){
	return pthread_mutex_unlock(&mutex);
}

pthread_mutex_t* Mutex::getMutex(){
	return &mutex;
}
