#include <Booths.h>
#include <iostream>

Booths::Booths(Platforms* plat, Queue* que):platforms(plat), queue(que){
	nOfBooths = 0;
	stop = false;

	//init graphic
	int lines = LINES * 0.7;
	int columns = COLS * 0.2;
	int orgDistance = COLS * 0.35;
	winBooths = new Graphics(lines, columns, LINES - lines,
							COLS - orgDistance, '*', '*');

	//start with single booth open
	addBooth();

	//create threads adding and removing booths
	pthread_create(&addBoothThread, NULL, &Booths::boothAdder, this);
	pthread_create(&rmBoothThread, NULL, &Booths::boothRemover, this);
}

Booths::~Booths(){
	//signal threads to stop
	stopThreads();

	pthread_join(addBoothThread, NULL);
	pthread_join(rmBoothThread, NULL);

	for(int i = 0; i < nOfBooths; ++i){
		deleteBooth(i);
	}

	delete winBooths;
}

//add new booth
void Booths::addBooth(){
	queue->boothsMutex->lock();

	if (nOfBooths < maxBooths){
		//if there can be one more create it
		booths[nOfBooths] = new Booth(nOfBooths, winBooths->getWin(), platforms, queue);
		nOfBooths++;
	}

	queue->boothsMutex->unlock();
}

//remove existing booth
void Booths::removeBooth(){
	queue->boothsMutex->lock();

	//one must remain
	if(1 < nOfBooths){
		nOfBooths--;
		deleteBooth(nOfBooths);
	}

	queue->boothsMutex->unlock();
}

void Booths::deleteBooth(int idx){
	//no need for mutex as it is held in removeBooth method
	booths[idx]->stopBooth();
	delete booths[idx];
	booths[idx] = NULL;
}

//booth adding thread main method
void* Booths::boothAdder(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	thisThread->queue->boothsMutex->lock();
	while(!thisThread->stop){
		//wait for queue to signal that it needs more booths
		pthread_cond_wait(&thisThread->queue->addCond,
				thisThread->queue->boothsMutex->getMutex());

		thisThread->queue->boothsMutex->unlock();
		//addBooth holds its own mutex
		thisThread->addBooth();
		thisThread->queue->boothsMutex->lock();
	}//exit locked
	thisThread->queue->boothsMutex->unlock();

	pthread_exit(NULL);
}

//booth adding thread main method
void* Booths::boothRemover(void* me){
	Booths* thisThread = static_cast<Booths*>(me);

	thisThread->queue->boothsMutex->lock();
	while(!thisThread->stop){
		//wait for queue to signal that there is no need for that many booths
		pthread_cond_wait(&thisThread->queue->rmCond,
				thisThread->queue->boothsMutex->getMutex());

		thisThread->queue->boothsMutex->unlock();
		//removeBooth holds its own lock
		thisThread->removeBooth();
		thisThread->queue->boothsMutex->lock();
	}//exit locked
	thisThread->queue->boothsMutex->unlock();

	pthread_exit(NULL);
}

//method stoping addBoothThread and rmBoothThread
void Booths::stopThreads(){
	queue->boothsMutex->lock();
	stop = true;
	//wake threads up
	pthread_cond_signal(&queue->addCond);
	pthread_cond_signal(&queue->rmCond);
	queue->boothsMutex->unlock();
}
