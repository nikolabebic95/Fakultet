monitor Allocation{
    int free = 3;
    conditionalVariable cv[2][2];

    void allocate(int amount, int priority){
        while(true){
            if(free >= amount){
                free -= amount;
                return;
            }
            
            cv[amount - 1][priority].wait();
        }
    }

    void free(int amount){
        free += amount;

        if(free == 2){
            if(!cv[1][1].empty()){
                cv[1][1].signal();
                return;
            }
            if(!cv[1][0].empty()){
                cv[1][0].signal();
                return;
            }
        }   
        
        int available = free;

        for(int i = 0; i < available; i++){
            if(!cv[0][1].empty()){
                cv[0][1].signal();
                available--;
            }
        }
        
        for(int i = 0; i < available; i++){
            if(!cv[0][0].empty()){
                cv[0][0].signal();
                available--;
            }
        }
    }
}