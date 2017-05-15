/*
 * Školsko jezgro proširuje se konceptom mutex koji predstavlja binarni semafor, poput događaja
 * (event), sa istom semantikom operacija wait i signal kao kod događaja, ali sa sledećim
 * dodatnim ograničenjima koja su u skladu sa namenom upotrebe samo za međusobno
 * isključenje kritične sekcije:
 * • inicijalna vrednost je uvek 1;
 * • operaciju signal može da pozove samo nit koja je zatvorila ulaz u kritičnu sekciju,
 * odnosno koja je pozvala operaciju wait; u suprotnom, operacija signal vraća grešku;
 * • nit koja je već zatvorila mutex operacijom wait, ne može ponovo izvršiti wait na
 * njemu.
 * Operacije wait i signal vraćaju celobrojnu vrednost, 0 u slučaju uspeha, negativnu vrednost u
 * slučaju greške. Prikazati implementaciju klase Mutex, po uzoru na klasu Semaphore prikazanu
 * na predavanjima (ne treba implementirati red čekanja niti, pretpostaviti da ta klasa postoji). 
 */

#include "Thread.h"
#include "Semaphore.h"

using namespace etfosthreading;

class Mutex{
public:
    int wait(){
        int ret;
        lock();
        if(Thread::running == thread_)
            ret=-1;
        else{
            semaphore_.wait();
            thread_=Thread::running;
            ret=0;
        }
        unlock();
        return ret;
    }
    int signal(){
        int ret;
        lock();
        if(Thread::running != thread_)
            ret=-1;
        else{
            semaphore_.signal();
            ret=0;
        }
        unlock();
        return ret;
    }
private:
    Semaphore semaphore_(1);
    Thread* thread_;
    void lock(); 
    void unlock();
};
