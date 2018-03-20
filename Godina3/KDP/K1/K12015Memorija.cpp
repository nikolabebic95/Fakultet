const int N = ...;
int free = N;
int cntBlocked = 0;
Semaphore mutexBlocked(1);
Semaphore mutexFree(1);
Semaphore semBlock(0);
Semaphore mutexPriority(1);
std::priority_queue<int> requests;

void request(int amount){
    mutexPriority.wait();
    requests.push(amount);
    mutexPriority.signal();

    while(true){
        mutexFree.wait();
        bool shouldBlock = false;

        if(amount > free){
            shouldBlock = true;
        }
        else{
            mutexPriority.wait();
            if(amount != requests.top()){
                mutexPriority.signal();
                mutexFree.signal();
                continue;
            }
            else{
                free -= amount;
                requests.pop();
            }
            mutexPriority.signal();
        }
        
        mutexFree.signal();

        if(shouldBlock){
            mutexBlocked.wait();
            cntBlocked++;
            mutexBlocked.signal();
            semBlock.wait();
        }
    }
}

void release(int amount){
    mutexFree.wait();
    free += amount;
    mutexFree.signal();

    mutexBlocked.wait();
    for(int i=0; i < cntBlocked; i++)
        semBlock.signal();
    cntBlocked = 0;
    mutexBlocked.signal();
}
