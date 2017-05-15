#ifndef SHAREDDATA_H_
#define SHAREDDATA_H_

#include <iostream>
#include "Semaphore.h"

using namespace std;
Semaphore semaphore_add(2);
Semaphore semaphore_get(0);
Semaphore mutex_add(1);

class SharedData {
public:
	SharedData():i(0){
	}
	void add(int itm){
		semaphore_add.wait();
		mutex_add.wait();
		a[i]=itm;
		i++;
		//if(i==2)
			semaphore_get.signal();
		mutex_add.signal();
	}

	int get(){
		semaphore_get.wait();
		semaphore_get.wait();
		int ret=a[0]+a[1];
		i=0;
		semaphore_add.signal();
		semaphore_add.signal();
		return ret;
	}

private:

	int i;
	int a[2];

	//add your code here

};

#endif /* SHAREDDATA_H_ */
