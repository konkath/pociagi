#include <RandomGenerator.h>

RandomGenerator::RandomGenerator(){
	random_device rd;
	mt19937 generate(rd());

	randomMutex = new Mutex(PTHREAD_MUTEX_DEFAULT);
}
RandomGenerator::~RandomGenerator(){
	delete randomMutex;
}

int RandomGenerator::getRandomInt(int begin, int end){
	randomMutex->lock();
	uniform_int_distribution<> rInt(begin, end);
	int temp = rInt(generate);
	randomMutex->unlock();

	return temp;
}
