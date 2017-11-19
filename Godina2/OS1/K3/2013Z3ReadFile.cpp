Byte* readFileBlock(FCB* file, BlkNo blockNo);

int fread(FCB* file, Byte* buffer, int n){
    if(file->cur>=file->size || file->cur<0)
        return 0;

    int block=file->cur/BLKSIZE;
    int byte=file->cur%BLKSIZE;
    Byte* fileBlock=readFileBlock(file, block);
    if(fileBlock==0)
        return 0;

    int i;
    for(i=0; i<n && file->cur<file->size, i++){
        if(byte==BLKSIZE){
            block++;
            byte=0;
            fileBlock=readFileBlock(file, block);
            if(fileBlock==0)
                return i;
        }

        buffer[i]=fileBlock[byte];
        byte++;
        file->cur++;
    }

    return i;
}