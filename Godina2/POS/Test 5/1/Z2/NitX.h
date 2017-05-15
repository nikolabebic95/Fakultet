#ifndef NITX_H_
#define NITX_H_

#include "Thread.h"
#include <iostream>
#include <stdlib.h>
#include "Semaphore.h"
#include <unistd.h>

using namespace std;

extern Semaphore semaphore1;
extern Semaphore semaphore2;

class NitX: public Thread {
public:
	NitX(char* threadName, int* counter) {
		this->cnt = counter;
		this->thrName = threadName;
	}
protected:
	virtual void run(){

		for (int i = 0; i < 10; ++ i) {
			usleep(rand()%1000); // sleep [1-1000] micro sec.
			semaphore1.wait();
			(*cnt)++;
			cout<<thrName<<" counter ="<<*cnt<<endl;
			semaphore1.signal();
		}
		semaphore2.wait();
		cout<<thrName<<" finished"<<endl;
		semaphore2.signal();
	}
private:
	int* cnt;
	char* thrName;
};

#endif /* NITX_H_ */
