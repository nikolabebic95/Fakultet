struct FCB{
    unsigned long index;
    ...
}

typedef unsigned long ulong;
extern const ulong IndexSize; // velicina niza koji sadrzi brojeve blokova
void* getPBlock(ulong pBlockNo);

void* getFileBlock(FCB* fcb, ulong lBlockNo){
    if(fcb==0) return 0;

    ulong block_number=lBlockNo/IndexSize;
    if(block_number>=IndexSize) return 0;

    if(fcb->index==0)
        return 0;
    ulong *head_block=(ulong*)getPBlock(fcb->index);
    if(head_block==0) return 0;
    if(head_block[block_number]==0)
        return 0;
    
    ulong *level2_block=(ulong*)getPBlock(head_block[block_number]);
    if(level2_block==0) return 0;
    return getPBlock(level2_block[lBlockNo%IndexSize]);
}