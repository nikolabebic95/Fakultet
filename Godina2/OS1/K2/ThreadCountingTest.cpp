/*Napisati program u kome glavna nit pokrece dve niti koje naizmenicno na standardni
izlaz ispisuju brojeve od 1 do 100.*/

#include "Thread.h"
#include "Semaphore.h"

static Semaphore odd_semaphore(1), even_semaphore(0);
static const size_t MAX=100;

class ThreadEven: public Thread{
private:
    
protected:
    void run() const override{
        for(auto i=2; i<=MAX; i+=2){
            even_semaphore.wait();
            std::cout<<i<<'\n';
            odd_semaphore.signal()
        }
    }
}

class ThreadOdd: public Thread{
protected:
    void run() const override{
        for(auto i=1; i<=MAX; i+=2){
            odd_semaphore.wait();
            cout<<i<<'\n';
            even_semaphore.signal();
        }
    }
}

int countingTest(){
    ThreadEven thread_even;
    ThreadOdd thread_odd;
    thread_even.start();
    thread_odd.start();

    thread_even.waitToComplete();
    thread_odd.waitToComplete();

    return 0;
}
