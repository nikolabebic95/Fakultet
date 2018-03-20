Semaphore entry(1);
Semapgore exit(1);
Semaphore capacity(N);
Semaphore gender(1);
Semaphore semMen(1);
Semaphore semWomen(1);
Semaphore semJanitor(1);
Semaphore kids(0);
Semaphore semKids(1);
void criticalSection();
int cntWomen = 0;
int cntMen = 0;
int cntKids = 0;
bool janitor = false;

void woman(int index){
    entry.wait();
    capacity.wait();

    semMen.wait();
    bool shouldBlock = false;
    if(cntMen > 0)
        shouldBlock = true;
    semMen.signal();
    if (shouldBlock)
        gender.wait();

    semJanitor.wait();
    if(janitor)
        shouldBlock = true;
    semJanitor.signal();
    if (shouldBlock)
        gender.wait();

    semWomen.wait();
    if (cntWomen == 0){
        gender.wait();
        //kids.signal();
    }
    cntWomen++;
    semWomen.signal();

    entry.signal();

    criticalSection();

    exit.wait();

    semWomen.wait();
    cntWomen--;
    if(cntWomen == 0){
        //kids.wait();
        gender.signal();
    }
    semWomen.signal();

    capacity.signal();

    exit.signal();
}

void man(int index){
    entry.wait();
    capacity.wait();

    semWomen.wait();
    bool shouldBlock = false;
    if(cntWomen > 0)
        shouldBlock = true;
    semWomen.signal();
    if (shouldBlock)
        gender.wait();

    semJanitor.wait();
    if(janitor)
        shouldBlock = true;
    semJanitor.signal();
    if (shouldBlock)
        gender.wait();

    semMen.wait();
    if (cntMen == 0){
        gender.wait();
        //kids.signal();
    }
    cntMen++;
    semMen.signal();

    entry.signal();

    criticalSection();

    exit.wait();

    semMen.wait();
    cntMen--;
    if(cntMen == 0){
        //kids.wait();
        gender.signal();
    }
    semMen.signal();

    capacity.signal();

    exit.signal();
}

void janitor(int index){
    entry.wait();

    semWomen.wait();
    bool shouldBlock = false;
    if(cntWomen > 0)
        shouldBlock = true;
    semWomen.signal();
    if (shouldBlock)
        gender.wait();

    semMen.wait();
    bool shouldBlock = false;
    if(cntMen > 0)
        shouldBlock = true;
    semMen.signal();
    if (shouldBlock)
        gender.wait();

    semJanitor.wait();
    if(janitor)
        shouldBlock = true;
    semJanitor.signal();
    if (shouldBlock)
        gender.wait();

    semJanitor.wait();
    if (!janitor){
        gender.wait();
    }
    janitor = true;
    semMen.signal();

    entry.signal();

    criticalSection();

    exit.wait();

    semJanitor.wait();
    janitor = false;
    gender.signal();
    semMen.signal();

    exit.signal();
}

void kid(int index){
    entry.wait();
    capacity.wait();

    semKids.wait();
    if(cntKids == 0)
        kids.wait();
    cntKids++;
    semKids.signal();

    entry.signal();

    criticalSection();

    semKids.wait();
    cntKids--;
    if(cntKids == 0)
        kids.signal();
    semKids.signal();

    capacity.signal();
}

void init(){

}
