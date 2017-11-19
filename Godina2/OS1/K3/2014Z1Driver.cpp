typedef ... Byte;
typedef ... BlkNo;

struct DiskOperationsTable {
 int (*readBlock)(BlkNo block, Byte* buffer);
 int (*writeBlock)(BlkNo block, Byte* buffer);
};

const int MaxNumOfDisks;
DiskOperationsTable* disks[MaxNumOfDisks];

int readBlock(int diskNo, BlkNo block, Byte* buffer){
    if(diskNo>=MaxNumOfDisks || diskNo<0 || disks[diskNo]==0)
        return -1;
    if(disks[diskNo]->readBlock==0)
        return -1;
    return (*(disks[diskNo]->readBlock))(block, buffer);
}

int writeBlock(int diskNo, BlkNo block, Byte* buffer){
    if(diskNo>=MaxNumOfDisks || diskNo<0 || disks[diskNo]==0)
        return -1;
    if(disks[diskNo]->writeBlock==0)
        return -1;
    return (*(disks[diskNo]->writeBlock))(block, buffer);
}