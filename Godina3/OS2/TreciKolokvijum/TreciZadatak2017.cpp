#define INPUT 0
#define OUTPUT 1
#define NUM ...
#define NUM_OF_ITERATIONS ...

int pLeft[NUM][2];
int pRight[NUM][2];

void f(int index, int& value, double& ratio){
    int value1 = value * ratio;
    int value2 = value - value1;
    write(pLeft[index], &value1, sizeof(int));
    write(pRight[(index + 1) % NUM], &value2, sizeof(int));
    read(pRight[index], &value1, sizeof(int));
    read(pLeft[(index + 1) % NUM], &value2, sizeof(int));
    value = value1 + value2;
    ratio = value1 / value;
}

void p(int index) {
    int value = index;
    double ratio = 0.5;

    for(int i = 0; i < NUM_OF_ITERATIONS; i++)
        f(index, value, ratio);

    
}

int main(){
    int index = 0;

    for(int i = 0; i < NUM; i++){
        pipe(pLeft[i]);
        pipe(pRight[i]);
    }

    for(int i = 0; i < NUM - 1; i++){
        if(fork() == 0){
            index = i + 1;
            break;
        }
    }

    p(index);

    for(int i = 0; i < NUM; i++){
        close(pLeft[i][INPUT]);
        close(pLeft[i][OUTPUT]);
        close(pRight[i][INPUT]);
        close(pRight[i][OUTPUT]);
    }
}