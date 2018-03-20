class Agent{
public:
    Agent(key_t key){
        finishedSmoking();
    }
    void takePaperAndMatch(){
        sem[0].wait();
    }

    void takeTobaccoAndMatch(){
        sem[1].wait();
    }

    void takeTobaccoAndPaper(){
        sem[2].wait();
    }

    void finishedSmoking(){
        missing = randNum();
        sem[missing].signal();
    }
private:
    Semaphore sem[3];
    int missing;
};
