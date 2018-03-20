int cntCustomers = 0;
Semaphore semCustomers(0);
Semaphore sleep(0);
Semaphore mutex(1);

void barber(){
    while(true){
        semCustomers.wait();
        bool blockBarber = false;
        if(cntCustomers == 0)
            blockBarber = true;
        semCustomers.signal();

        if(blockBarber)
            sleep.wait();

        mutex.signal();

        semCustomers.wait();
        cntCustomers--;
        semCustomers.signal();
    }
}

void customer(){
    semCustomers.wait();
    if(cntCustomers == N){
        semCustomers.signal();
        return;
    }

    if(cntCustomers == 0){
        cntCustomers++;
        sleep.signal();
    }
    else{
        cntCustomers++;
    }
    semCustomers.signal();

    mutex.wait();
}
