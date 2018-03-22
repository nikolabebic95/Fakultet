void enter(int* lock){
    while(testAndSet(lock));
}

void exit(int* lock){
    lock = 0;
}

// Optimizacija
void enterOptimized(int* lock){
    while(true){
        while(*lock);

        if(!testAndSet(lock))
            break;
    }
}
