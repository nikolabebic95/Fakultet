Semaphore semArray[N]; // Inicijalizovani su na 0!
Semaphore capacity(N);
Semaphore mutexPut(1);
Semaphore mutexGet(1);
Semaphore semEmpty(N);
int head = 0, tail = 0;

void driver(){
    while(true){
        semEmpty.wait();

        mutexGet.wait();
        semArray[head].signal();
        head = (head + 1) % N;
        mutexGet.signal();

        // drive
    }
}

void car(){
    while(true){
        mutexPut.wait();
        int t = tail;
        tail = (tail + 1) % N;
        mutexPut.signal();

        semEmpty.signal();

        semArray[t].wait();

        // drive
    }
}
