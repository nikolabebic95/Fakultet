int counter = 0;
int next = 0;

void process(int index){
    int turn;
    <turn = counter++>;
    <await(next == turn)>
    // Critical section
    next++;
}

// Fine grain

int lock = 0;

void fineGrainProcess(int index){
    int turn;
    while(testAndSet(&lock));
    turn = counter++;
    lock = 0;

    while(next != turn);
    // Critical section
    next++;
}
