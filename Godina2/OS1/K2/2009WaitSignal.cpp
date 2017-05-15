/*
 * Realizaciju semafora pomocu C++ klase Semaphore date na predavanjima modifikovati tako da se 
 * promena konteksta moze dogoditi i kod neblokirajucih poziva wait i signal na semaforu(tj.pri svakom 
 * pozivu signal, kao i pri pozivu wait i kada ne treba blokirati pozivajuci proces).
 */

void Semaphore::wait() {
    lock();
    if (--val < 0) block();
    else yield();
    unlock();
}

void Semaphore::signal() {
    lock();
    if (val++ < 0) deblock();
    yield();
    unlock();
}
