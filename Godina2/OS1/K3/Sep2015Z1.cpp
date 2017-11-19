void writeBlock(IOHandle handle, char* addr);

void putchar(IOHandle handle, char c){
    static char block[BlockSize];
    static int already_written=0;
    block[already_written++]=c;
    if(already_written==BlockSize){
        already_written=0;
        writeBlock(handle, block);
    }
}