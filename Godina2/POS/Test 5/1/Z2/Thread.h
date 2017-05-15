#include <pthread.h>
#include <iostream>

#ifndef THREAD_H_
#define THREAD_H_

class Thread {
public:
	void start();
	void waitToComplete(){
		pthread_join(tid,NULL);
	}

	static void dispose(Thread* t){
		t->waitToComplete();
		delete t;
	}


protected:
	virtual void run() = 0;

	virtual ~Thread() {}

	static void* starter(void* thread);

	pthread_t tid;

};

#endif /* THREAD_H_ */
