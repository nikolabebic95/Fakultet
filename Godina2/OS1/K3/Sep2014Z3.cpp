PBlock getFilePBlockNo(FCB* fcb, unsigned long byte){
    unsigned int entry_number=byte/BlockSize;
    if(entry_number<SingleIndexSize)
        return fcb->singleIndex[entry_number];
    entry_number-=SingleIndexSize;
    unsigned int block_number=entry_number/DblIndex1Size;

    PBlock *block_array=(PBlock*)getDiskBlock(dblIndex[block_number]);
    return block_array[entry_number%DblIndex1Size];

}