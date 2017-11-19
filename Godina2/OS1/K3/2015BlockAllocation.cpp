typedef unsigned char byte;
const unsigned int BITS_IN_BYTE = 8;
const unsigned long NumOfBlocks = ...;
byte blocks[NumOfBlocks/BITS_IN_BYTE];

//a)

void blockToBit(unsigned long blkNo, unsigned long& bt, byte& mask){
    bt=blkNo/BITS_IN_BYTE;
    mask=1;
    mask<<=blkNo%BITS_IN_BYTE;
}

void bitToBlk(unsigned long& blkNo, unsigned long bt, byte mask){
    int counter=-1;
    while(mask!=0){
        counter++;
        mask>>=1;
    }
    blkNo=bt*8+counter;
}

//b)

unsigned long allocateBlock(unsigned long startingFrom){
    for(int i=startingFrom/8*8; i<NumOfBlocks; i++){
        unsigned long bt;
        byte mask;
        blockToBit(i, bt, mask);
        if(!(blocks[bt] & mask)){
            blocks[bt]=blocks[bt] | mask;
            return i;
        }
    }

    for(int i=1; i<startingFrom/8*8-1; i++){
        unsigned long bt;
        byte mask;
        blockToBit(i, bt, mask);
        if(!(blocks[bt] & mask)){
            blocks[bt]=blocks[bt] | mask;
            return i;
        }
    }

    return 0;
}

void freeBlock(unsigned long blk){
    if(blk>=NumOfBlocks || blk<0)
        return;
    unsigned long bt;
    byte mask;
    blockToBit(blk, bt, mask);
    mask=~mask;
    blocks[bt]=blocks[bt] & mask;
}
