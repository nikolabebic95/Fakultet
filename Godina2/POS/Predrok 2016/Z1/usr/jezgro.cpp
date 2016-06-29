#include <iostream>
#include <unistd.h>
#include "Matrix.h"
#include "Thread.h"
#include "NitX.h"
#include "Semaphore.h"

using namespace std;

Semaphore sem(1);
Matrix M(10, 10);

int main(){

	cout<< "START"<<endl;
	
	M.print();

	Thread* t1 = new NitX("T1");
	Thread* t2 = new NitX("T2");

	t1->start();
	t2->start();

	Thread::dispose(t1);
	Thread::dispose(t2);

	cout<< endl<< "RESULT" << endl;
	M.print();

	cout<< "END" << endl;

	pthread_exit(NULL);

}


