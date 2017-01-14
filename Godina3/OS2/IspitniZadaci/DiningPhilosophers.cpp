//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2 
//  Dining philosophers
//  Implementacija koja koristi deadlock-prevention
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  Januar 2015.
//  Koriscenjem standardnih brojackih semafora, napisati jedno resenje problema filozofa koje
//  nema ni problem mrtve blokade, ni zive blokade, ni izgladnjivanja.
// 
//==========================================================================================================//
//==========================================================================================================//

#include <Semaphore.h>

const size_t NUM_OF_PHILOSOPHERS = ...;

Semaphore forks[NUM_OF_PHILOSOPHERS];
Semaphore deadlockPrevention;

void initialize() {
    for (auto &fork : forks) {
        fork.setValue(1);
    }

    deadlockPrevention.setValue(NUM_OF_PHILOSOPHERS - 1);
}

void philosopherThread(size_t index) {
    auto left = index;
    auto right = (index + 1) % NUM_OF_PHILOSOPHERS;

    while (true) {
        think();
        deadlockPrevention.wait();
        
        forks[left].wait();
        forks[right].wait();

        eat();

        forks[left].signal();
        forks[right].signal();

        deadlockPrevention.signal();
    }
}

int main() {
    initialize();

    std::vector<std::thread> vect;

    for (size_t i = 0; i < NUM_OF_PHILOSOPHERS; i++) {
        vect.push_back(std::thread(philosopherThread, i));
    }

    for (size_t i = 0; i < NUM_OF_PHILOSOPHERS; i++) {
        vect[i].join();
    }

    return 0;
}
