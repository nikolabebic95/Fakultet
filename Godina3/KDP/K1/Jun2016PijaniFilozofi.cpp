Semaphore matrix[N][M]; // M je maksimalan broj pica izmedju dva filozofa, inicijalizovano na 1
Semaphore deadlockPrevention(N - 1);

void philosopher(int index){
    int left = index;
    int right = (index + 1) % N;

    while(true){
        deadlockPrevention.wait();

        std::vector<int> wantedDrinksLeft = getWantedDrinksLeftSorted();
        for(int i: wantedDrinksLeft){
            matrix[left][i].wait();
            takeDrink(left, i);
        }
        std::vector<int> wantedDrinksRight = getWantedDrinksRightSorted();
        for(int i: wantedDrinksRight){
            matrix[right][i].wait();
            takeDrink(right, i);
        }

        // drinking

        for(int i: wantedDrinksLeft)
            matrix[left][i].signal();
        for(int i: wantedDrinksRight)
            matrix[right][i].signal();

        deadlockPrevention.signal();
    }
}

int main(){
    
}