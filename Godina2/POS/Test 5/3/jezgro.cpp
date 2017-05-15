#include <iostream>
#include <unistd.h>
#include "Thread.h"
#include "NitX.h"

using namespace std;

Semaphore semaphore1(1);
Semaphore semaphore2(0);

int main(){

	cout<< "START"<<endl;

	int counter = 0;

	Thread* t1 = new NitX("T1",&counter, &semaphore1, &semaphore2);
	Thread* t2 = new NitX("T2",&counter, &semaphore2, &semaphore1);

	t1->start();
	t2->start();

	Thread::dispose(t1);
	Thread::dispose(t2);

	cout<< "END"<<endl;

	pthread_exit(NULL);

}

