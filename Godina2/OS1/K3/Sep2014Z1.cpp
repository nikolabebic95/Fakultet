void readBlock(char* addr);

char getchar(){
    static char block[BlockSize];
    static int num_of_chars=0;

    if(num_of_chars==0){
        readBlock(block);
        num_of_chars=BlockSize;
    }

    char ret=block[BlockSize-num_of_chars];
    num_of_chars--;
    return ret;
}