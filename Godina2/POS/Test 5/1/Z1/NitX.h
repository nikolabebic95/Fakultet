#ifndef NITX_H_
#define NITX_H_

#include "Thread.h"
#include <iostream>
#include "Semaphore.h"
#include "SharedData.h"
#include <stdlib.h>
#include <unistd.h>


using namespace std;
extern Semaphore mutex;

class NitX: public Thread {
public:
	NitX(SharedData* data, int ii) {
		this->data = data;
		this->num = ii;
	}
protected:
	virtual void run(){

		for (int i = 0; i < 10; ++ i) {

			data->add(i);

			mutex.wait();
			cout<<"Producer"<<num<<" produced: "<<i<<endl;
			mutex.signal();


			usleep(rand()%1000); // sleep [1-1000] micro sec.


		}
		mutex.wait();
		cout<<"Producer"<<num<<" finished"<<endl;
		mutex.signal();
	}
private:
	SharedData* data;
	int num;
};

#endif /* NITX_H_ */
