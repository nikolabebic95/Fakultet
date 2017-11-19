typedef ... Byte;
typedef ... BlkNo;

typedef int (*DiskOperation)(BlkNo block, Byte* buffer);

struct DiskOperationsTable{
    int isValid;
    DiskOperation readBlock, writeBlock;
    DiskOperationsTable(): isValid(0), readBlock(0), writeBlock(0){}
}

const int MaxNumOfDisks;
DiskOperationsTable disks[MaxNumOfDisks];

//a)

int readBlock(int diskNo, BlkNo block, Byte* buffer){
    if(diskNo>=MaxNumOfDisks || diskNo<0 || disks[diskNo].isValid==0)
        return -1;
    else
        return disks[diskNo].readBlock(block, buffer);
}

int writeBlock(int diskNo, BlkNo block, Byte* buffer){
    if(diskNo>=MaxNumOfDisks || diskNo<0 || disks[diskNo].isValid==0)
        return -1;
    else
        return disks[diskNo].writeBlock(block, buffer);
}

//b)

int registerDriver(int diskNo, DiskOperation read, DiskOperation write){
    if(diskNo>=MaxNumOfDisks || diskNo<0 || disks[diskNo].isValid==1)
        return -1;
    else{
        disks[diskNo].readBlock=read;
        disks[diskNo].writeBlock=write;
        disks[diskNo].isValid=1;
        return 0;
    }
}