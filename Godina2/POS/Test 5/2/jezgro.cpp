#include <iostream>
#include <unistd.h>
#include "Thread.h"
#include "NitX.h"

using namespace std;

Semaphore semaphore1(1);
Semaphore semaphore2(1);

int main(){

	cout<< "START"<<endl;

	Thread* t1 = new NitX("T1");
	Thread* t2 = new NitX("T2");
	Thread* t3 = new NitX("T3");

	t1->start();
	t2->start();
	t3->start();

	Thread::dispose(t1);
	Thread::dispose(t2);
	Thread::dispose(t3);

	cout<< "END"<<endl;

	pthread_exit(NULL);
}

