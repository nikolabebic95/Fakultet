class Buffer{
public:
    Buffer();
    void put(Byte b);
    void read(Byte block[]);
private:
    char buffer[BufferSize];
    int head, tail;
    int counter;
    Semaphore putM, readM, putS, readS;
}

Buffer::Buffer(): head(0), tail(0), counter(0), putM(1), readM(1), putS(BufferSize), readS(0){}

void Buffer::put(Byte b){
    putS.wait();
    putM.wait();

    buffer[tail]=b;
    tail=(tail+1)%BufferSize;
    counter++;

    if(counter==BlockSize){
        counter=0;
        readS.signal();
    }
    putM.signal();
}

void Buffer::read(Byte block[]){
    readS.wait();
    readM.wait();

    for(int i=0; i<BlockSize; i++){
        block[i]=buffer[head];
        head=(head+1)%BufferSize;
        putS.signal();
    }

    readM.signal();
}