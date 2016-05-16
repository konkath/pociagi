#include <Mutex.h>

Mutex::Mutex(int type){
	//create mutex attribute
	pthread_mutexattr_init(&attr);

	if (type == PTHREAD_MUTEX_RECURSIVE){
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	}else{
		//default mutex
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
	}

	//create mutex
	pthread_mutex_init(&mutex, &attr);
}

Mutex::~Mutex(){
	//destroy mutex and its attribute
	pthread_mutex_destroy(&mutex);
	pthread_mutexattr_destroy(&attr);
}

int Mutex::lock(){
	return pthread_mutex_lock(&mutex);
}

int Mutex::unlock(){
	return pthread_mutex_unlock(&mutex);
}

//return reference to mutex (needed in conditional variables)
pthread_mutex_t* Mutex::getMutex(){
	return &mutex;
}
