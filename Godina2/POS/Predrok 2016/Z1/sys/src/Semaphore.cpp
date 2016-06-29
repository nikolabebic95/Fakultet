#include "Semaphore.h"

Semaphore::Semaphore(int initial = 0) {
	sem_init(&sem,0,initial);
}

Semaphore::~Semaphore(){
	sem_destroy(&sem);
}

void Semaphore::wait(){
	sem_wait(&sem);
}

void Semaphore::signal(){
	sem_post(&sem);
}
