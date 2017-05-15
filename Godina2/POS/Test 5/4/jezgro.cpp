#include <iostream>
#include <unistd.h>
#include "Thread.h"
#include "NitX.h"
#include <ctime>

using namespace std;

Semaphore semaphore1(1);
Semaphore semaphore2(0);

int main(){
	srand((unsigned)time(NULL));
	cout<< "START"<<endl;

	int counter = 0;

	Thread* t1 = new NitX("T1",&counter);
	Thread* t2 = new NitX("T2",&counter);

	t1->start();
	t2->start();

	Thread::dispose(t1);
	Thread::dispose(t2);

	cout<< "END"<<endl;

	pthread_exit(NULL);
}

