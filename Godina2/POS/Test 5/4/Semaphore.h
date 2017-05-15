#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <semaphore.h>

class Semaphore {

public:
  Semaphore(int initial = 0) {
	  sem_init(&sem,0,initial);
  }

  ~Semaphore(){
	  sem_destroy(&sem);
   }

  void wait(){
	  sem_wait(&sem);
  }

  void signal(){
	  sem_post(&sem);

  }

private:
  sem_t sem;

};

#endif /* SEMAPHORE_H_ */
