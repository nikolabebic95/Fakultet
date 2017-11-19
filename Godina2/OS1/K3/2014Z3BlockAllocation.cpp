typedef … BlockNo;
extern int blockSize;
void* getBlock (BlockNo block);
extern BlockNo freeBlocksHead;

BlockNo getFreeBlock (){
    if(freeBlocksHead == 0)
        return 0;
    
    int N=blockSize/sizeof(BlockNo);
    BlockNo first=freeBlocksHead;
    BlockNo* blockNoPtr=(BlockNo*)getBlock(first);
    int i;
    for(i=0; i<N-1; i++)
        if(blockNoPtr[i]!=0) break;
    
    if(i<N-1){
        BlockNo ret=blockNoPtr[i];
        blockNoPtr[i]=0;
        return ret;
    }

    freeBlocksHead=blockNoPtr[N-1];
    return first;
}