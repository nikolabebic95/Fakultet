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
static bool first=true;
static Semaphore mutex(1);
static Semaphore mutex_write(1);

class NitX: public Thread {
public:
	NitX(string threadName, int* counter) {
		this->cnt = counter;
		this->thrName = threadName;
	}
protected:
	virtual void run(){
		usleep(rand()%1000);
		Semaphore *sem1, *sem2;
		mutex.wait();
		if(first){
			first=false;
			sem1=&semaphore1;
			sem2=&semaphore2;
		}
		else{
			sem1=&semaphore2;
			sem2=&semaphore1;
		}
		mutex.signal();
		for (int i = 0; i < 10; ++ i) {
			usleep(rand()%1000); // sleep [1-1000] micro sec.
			sem1->wait();
			(*cnt)++;
			cout<<thrName<<" counter ="<<*cnt<<endl;
			sem2->signal();
		}
		mutex_write.wait();
		cout<<thrName<<" finished"<<endl;
		mutex_write.signal();
	}
private:
	int* cnt;
	string thrName;
};

#endif /* NITX_H_ */
