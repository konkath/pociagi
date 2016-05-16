/*
 * SignalLight.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include <SignalLight.h>

SignalLight::SignalLight(){
	greenLight = false;
	stop = false;
	redTimer = 5000, greenTimer = 1000;

	int lines = LINES * 0.1;
	int columns = COLS * 0.6;

	Graphics::createWindow(winSignal, lines, columns, 2, 2);
	Graphics::createBox(winSignal, '+', '+');
	Graphics::setColor(winSignal, 1);

	lightMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	stopMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	pthread_cond_init(&lightCond, NULL);

	pthread_create(&lightThread, NULL, &SignalLight::lightChanger, this);
}

SignalLight::~SignalLight(){
	stopMutex->lock();
	stop = true;
	stopMutex->unlock();

	pthread_join(lightThread, NULL);

	Graphics::deleteWindow(winSignal);

	delete lightMutex;
	delete stopMutex;
	pthread_cond_destroy(&lightCond);
}

bool SignalLight::isGreen(){
	lightMutex->lock();
	bool result = greenLight;
	lightMutex->unlock();

	return result;
}

void SignalLight::changeColor(){
	lightMutex->lock();
	greenLight = !greenLight;

	if(greenLight){	//locked
		pthread_cond_signal(&lightCond);
		lightMutex->unlock();

		Graphics::setColor(winSignal, 2);
	}else{
		lightMutex->unlock();

		Graphics::setColor(winSignal, 1);
	}//exit unlocked
}

void SignalLight::setGreen(){
	lightMutex->lock();
	greenLight = true;
	lightMutex->unlock();

	Graphics::setColor(winSignal, 2);
}

void SignalLight::setRed(){
	lightMutex->lock();
	greenLight = false;
	lightMutex->unlock();

	Graphics::setColor(winSignal, 1);
}

void* SignalLight::lightChanger(void* me){
	SignalLight* thisThread = static_cast<SignalLight*>(me);

	thisThread->stopMutex->lock();
	while(!thisThread->stop){
		thisThread->stopMutex->unlock();

		thisThread->setRed();
		usleep(thisThread->redTimer * 1000);

		thisThread->stopMutex->lock();
		if(thisThread->stop){
			thisThread->stopMutex->unlock();
			pthread_exit(NULL);
		}
		thisThread->stopMutex->unlock();

		thisThread->setGreen();

		thisThread->lightMutex->lock();
		pthread_cond_signal(&thisThread->lightCond);
		thisThread->lightMutex->unlock();

		usleep(thisThread->greenTimer * 1000);

		thisThread->stopMutex->lock();
	}//exit locked
	thisThread->stopMutex->unlock();

	pthread_exit(NULL);
}
