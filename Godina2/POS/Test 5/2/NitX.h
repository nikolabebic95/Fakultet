#ifndef NITX_H_
#define NITX_H_

#include "Thread.h"
#include <iostream>
#include <stdlib.h>
#include "Semaphore.h"
#include <unistd.h>

Semaphore mutex(1);

using namespace std;

class NitX: public Thread {
public:
	NitX(string threadName) {
		this->thrName = threadName;
	}
protected:
	virtual void run(){
		mutex.wait();
		cout<<"I am "<<thrName<<endl;
		mutex.signal();
	}
private:
	string thrName;
};

#endif /* NITX_H_ */
