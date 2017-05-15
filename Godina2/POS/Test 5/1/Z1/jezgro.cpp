#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Thread.h"
#include "NitX.h"
#include "NitY.h"
#include "Semaphore.h"

using namespace std;
Semaphore mutex(1);

int main(){

	cout<< "START"<<endl;


	SharedData data;

	Thread* t1 = new NitX(&data,1);
	Thread* t2 = new NitX(&data,2);

	Thread* t3 = new NitY(&data);

	t1->start();
	t2->start();

	t3->start();


	Thread::dispose(t1);
	Thread::dispose(t2);
	Thread::dispose(t3);

	cout<< "END"<<endl;

	pthread_exit(NULL);

}


