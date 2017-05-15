#ifndef NITY_H_
#define NITY_H_

#include "Thread.h"
#include <iostream>
#include "Semaphore.h"
#include "SharedData.h"
#include <stdlib.h>
#include <unistd.h>


extern Semaphore mutex;

using namespace std;

class NitY: public Thread {
public:
	NitY(SharedData* data) {
		this->data = data;
	}
protected:
	virtual void run(){

	for (int i = 0; i < 10; ++i) {

		int x = data->get();

		mutex.wait();
		cout << "Consumed :" <<x<<endl;
		mutex.signal();

		usleep(rand()%1000); // sleep [1-1000] micro sec.


		}
		mutex.wait();
		cout << "Consumer finished" << endl;
		mutex.signal();
	}

private:
	SharedData* data;
};

#endif /* NITY_H_ */
