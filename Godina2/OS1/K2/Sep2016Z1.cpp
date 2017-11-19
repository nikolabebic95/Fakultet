class Thread{
public:
    ...
    void send(char* message);
    static char* receive();
private:
    ...
    char* message=0;
    Semaphore sendSem(1), receiveSem(0);
}

void Thread::send(char* m){
    sendSem.wait();
    message=m;
    receiveSem.signal();
}

char* Thread::receive(){
    Thread::running->receiveSem.wait();
    char *ret=Thread::running->message;
    Thread::running->sendSem.signal();
    return ret;
}