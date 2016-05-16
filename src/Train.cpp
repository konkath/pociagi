#include <Train.h>

Train::Train(SignalLight* signal, Platforms* platforms, Queue* queue, int idx)
			:signalLight(signal), platforms(platforms), queue(queue), idx(idx){
	freeSeats = 30;
	passengersOut = 0;

	initThread();
	initGraphic(idx);

	pthread_create(&trainThread, NULL, &Train::conductor, this);
}

//konstruktor losowego pociagu
Train::Train(SignalLight* signal, Platforms* platforms, Queue* queue, int idx,
		int passengersOut, int freeSeats):signalLight(signal), platforms(platforms),
		queue(queue), idx(idx), freeSeats(freeSeats), passengersOut(passengersOut){

	initThread();
	initGraphic(idx);

	pthread_create(&trainThread, NULL, &Train::conductor, this);
}

Train::~Train(){
	pthread_join(trainThread, NULL);

	delete winTrain;
	delete passengersMutex;
	delete seatsMutex;
	delete statusMutex;
	delete stopMutex;
}

void Train::sendStop(){
	stopMutex->lock();
	stop = true;
	stopMutex->unlock();
}

bool Train::isReady(){
	statusMutex->lock();
	bool result = status == "C" ? true : false;
	statusMutex->unlock();

	return result;
}

void Train::initThread(){
	passengersMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	seatsMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	statusMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
	stopMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
}

void Train::initGraphic(int idx){
	int lines = LINES * 0.5;
	int columns = COLS * 0.08;
	int orgDistance = COLS * 0.48;

	int platform = platforms->getPlatform(idx);
	int id = platforms->getId(idx);

	if (1 == platform){
		orgDistance += COLS * 0.30;
	}

	if (1 == id){
		orgDistance += COLS * 0.2;
	}

	winTrain = new Graphics(lines, columns,	LINES - lines, COLS - orgDistance,
			'8', '!');

	timeoutMS = 100;
	status = "R";
	stop = false;
	reportPassengers();
}

void Train::reportPassengers(){
	//wysiadajacy + wolne miejsca
	string str[3];

	passengersMutex->lock();
	str[0] = "wy: " + to_string(passengersOut);
	passengersMutex->unlock();

	seatsMutex->lock();
	str[1] = "ws: " + to_string(freeSeats);
	seatsMutex->unlock();

	statusMutex->lock();
	str[2] = status;
	statusMutex->unlock();

	winTrain->showInMiddle(str, 3);
}

void* Train::conductor(void* me){
	Train* thisThread = static_cast<Train*>(me);

	thisThread->statusMutex->lock();
	thisThread->status = "R";
	thisThread->statusMutex->unlock();

	thisThread->passengersMutex->lock();
	while(thisThread->passengersOut != 0){
		thisThread->passengersOut--;
		thisThread->passengersMutex->unlock();

		thisThread->seatsMutex->lock();
		thisThread->freeSeats++;
		thisThread->seatsMutex->unlock();

		thisThread->queue->addPeople();
		thisThread->reportPassengers();

		usleep(thisThread->timeoutMS * 1000);

		thisThread->stopMutex->lock();
		if(thisThread->stop){
			thisThread->stopMutex->unlock();
			pthread_exit(NULL);
		}
		thisThread->stopMutex->unlock();

		thisThread->passengersMutex->lock();
	}
	thisThread->passengersMutex->unlock();

	thisThread->statusMutex->lock();
	thisThread->status = "Z";
	thisThread->statusMutex->unlock();

	thisThread->seatsMutex->lock();
	while(thisThread->freeSeats != 0){
		thisThread->seatsMutex->unlock();

		if(thisThread->platforms->removePeople(thisThread->idx)){
			thisThread->seatsMutex->lock();
			thisThread->freeSeats--;
			thisThread->seatsMutex->unlock();
		}

		thisThread->reportPassengers();
		usleep(thisThread->timeoutMS * 1000);

		thisThread->stopMutex->lock();
		if(thisThread->stop){
			thisThread->stopMutex->unlock();
			pthread_exit(NULL);
		}
		thisThread->stopMutex->unlock();

		thisThread->seatsMutex->lock();
	}
	thisThread->seatsMutex->unlock();

	thisThread->statusMutex->lock();
	thisThread->status = "C";
	thisThread->statusMutex->unlock();

	thisThread->reportPassengers();

	pthread_exit(NULL);
}

