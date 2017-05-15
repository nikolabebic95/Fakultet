#include "Thread.h"

void* Thread::starter(void* thr){

	Thread* t = (Thread*) thr;
	if (t!=NULL) {
		t->run();
	}

	pthread_exit(NULL);
}


void Thread::start(){
	pthread_create(&tid,NULL,&starter, this);
}
