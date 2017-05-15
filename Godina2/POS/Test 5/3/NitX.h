#ifndef NITX_H_
#define NITX_H_

#include "Thread.h"
#include <iostream>
#include <stdlib.h>
#include "Semaphore.h"
#include <unistd.h>

using namespace std;

static Semaphore mutex(1);

class NitX: public Thread {
public:
	NitX(string threadName, int* counter, Semaphore* sem1, Semaphore* sem2) {
		this->cnt = counter;
		this->thrName = threadName;
		sem1_=sem1;
		sem2_=sem2;
	}
protected:
	virtual void run(){

		for (int i = 0; i < 10; ++ i) {
			usleep(rand()%1000); // sleep [1-1000] micro sec.
			sem1_->wait();
			(*cnt)++;
			cout<<thrName<<" counter ="<<*cnt<<endl;
			sem2_->signal();
		}
		mutex.wait();
		cout<<thrName<<" finished"<<endl;
		mutex.signal();
	}
private:
	int* cnt;
	string thrName;
	Semaphore *sem1_, *sem2_;
};

#endif /* NITX_H_ */
