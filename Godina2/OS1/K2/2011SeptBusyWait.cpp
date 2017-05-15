/*
 * Izmeniti datu implementaciju operacije wait na semaforu u školskom jezru tako da, 
 * pre nego što odmah blokira pozivajuću nit ukoliko je semafor zatvoren, najpre pokuša
 * da uposleno sačeka, ali ograničeno, ponavljajući petlju čekanja najviše SemWaitLimit puta. 
 * Ostatak klase Semaphore se ne menja.
 */

void lock (int lck);
void unlock (int lck);

void Semaphore::oldWait(){
    lock(lck);
    if(--val<0)
        block();
    unlock(lck);
}

void Semaphore::newWait(){
    for(int i=0; i<SemWaitLimit && val<1; i++);
    lock(lck);
    --val;

    if(val<0)
        block();
    unlock(lck);
}
