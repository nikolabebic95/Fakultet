#ifndef NITX_H_
#define NITX_H_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Thread.h"
#include "Matrix.h"
#include "Semaphore.h"

using namespace std;

extern Semaphore sem;
extern Matrix M;

bool flag = false;

class NitX: public Thread {
public:
	NitX(const char* threadName) {
		this->thrName = threadName;
		
	}
public:
	virtual void run(){
		int i = 0;
		int j = 0;
		int end = 5;
		int number = 0;
		sem.wait();
		if (flag == false) flag = true;
		else {
			i = 5;
			end = 10;
			number = 1;
		}
		sem.signal();
		for (; i < end; i++) {
			for (j = 0; j < 10; j++) {
				M.setValue(i, j, number);
				usleep(rand()%1000); // sleep [1-1000] micro sec.
			}
		}

		cout<<thrName<<" finished"<<endl;
	}

private:
	const char* thrName;
};

#endif /* NITX_H_ */
