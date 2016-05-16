#include <Booth.h>
#include <iostream>

Booth::Booth(int id, WINDOW*& parent, Platforms* plat, Queue* que)
			:platforms(plat), queue(que){
	free = true;
	stop = false;
	timerMS = 500;

	randomGenerator = new RandomGenerator();
	stopMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);

	//initialize window
	int lines, columns;
	getmaxyx(parent, lines, columns);
	winBooth = new Graphics(parent, (lines - 2) * 0.3, columns - 2,
							1 + ((lines * 0.3) * id), 1, '#', '#');

	reportStatus();

	//create thread
	pthread_create(&queThread, NULL, &Booth::serve, this);
}

Booth::~Booth(){
	pthread_join(queThread, NULL);

	delete winBooth;
	delete randomGenerator;
	delete stopMutex;
}

//send stop signal to thread
void Booth::stopBooth(){
	stopMutex->lock();
	stop = true;
	stopMutex->unlock();
}

//report current booth status
//(no need for mutex as it is used for single thread only)
void Booth::reportStatus(){
	string str[1];
	if(free){
		str[0] = "W";
		winBooth->showInMiddle(str, 1);
	}else{
		str[0] = "Z";
		winBooth->showInMiddle(str, 1);
	}
}

//main thread function
void* Booth::serve(void* me){
	Booth* thisThread = static_cast<Booth*>(me);

	thisThread->stopMutex->lock();
	while(!thisThread->stop){
		thisThread->stopMutex->unlock();

		//report for user if booth did something or not
		thisThread->free = true;

		//if there are people in queue
		if(thisThread->queue->isEmpty()){
			//remove one
			thisThread->queue->removePeople();
			//add it to random platform
			thisThread->platforms->addPeople
			(thisThread->randomGenerator->getRandomInt(0, 3));
			//booth did something
			thisThread->free = false;
		}

		thisThread->reportStatus();
		usleep(thisThread->timerMS * 1000);

		thisThread->stopMutex->lock();
	}//exit locked
	thisThread->stopMutex->unlock();

	pthread_exit(NULL);
}
