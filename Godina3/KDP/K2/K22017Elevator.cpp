const int N = ...;

int elevatorFloor = 0;
int inside[N] = {0};
int outside[N] = {0};

void passenger(){
    while(true){
        // ...

        auto curr = getCurrentFloor();
        int wanted = getWantedFloor();

        region(elevatorFloor){
            outside[curr]++;
            <await(elevatorFloor == curr);>
            outside[curr]--;
            
            inside[wanted]++;
            <await(wanted == elevatorFloor);>
            inside[wanted]--;
        }

        // ...
    }
}

void elevator(){
    while(true){
        region(elevatorFloor){
            if(outside[elevatorFloor] != 0 || inside[elevatorFloor] != 0){
                <await(inside[elevatorFloor] == 0);>
                <await(outside[elevatorFloor] == 0);>
            }
            elevatorFloor = (elevatorFloor + 1) % N;
        }
    }
}
