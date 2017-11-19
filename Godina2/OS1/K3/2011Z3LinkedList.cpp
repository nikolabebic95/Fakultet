FATEntry FAT[...];
struct FATEntry{
    int next;
    FID fid;
}

struct FCB{
    FID id;
    FATEntry head;
}

int check_consistency(FCB* file){
    if(file==0)
        return 0;

    FID fid=file->id;
    FATEntry prev=0;
    FATEntry curr=file->head;

    while(curr!=0 && FAT[curr].fid==fid){
        prev=curr;
        curr=FAT[curr].next;
    }

    if(curr==0)
        return 1;

    if(prev==0)
        file->head=0;
    else
        FAT[prev].next=0;
    return 0;
}