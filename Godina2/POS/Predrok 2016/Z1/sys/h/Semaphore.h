#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <semaphore.h>

class Semaphore {

public:
  Semaphore(int initial);

  ~Semaphore();

  void wait();

  void signal();

private:
  sem_t sem;

};

#endif /* SEMAPHORE_H_ */
