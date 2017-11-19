const int OP_RD=4;
const int OP_WR=2;
const int OP_EX=1;

int lock(FCB* file, unsigned int op){
    if(op & OP_WR){
        if(file->sharedLock!=0 || file->exclLock!=0)
            return 0;
        else{
            file->exclLock=1;
            return 1;
        }
    }
    if(op & OP_RD || op & OP_EX){
        if(file->exclLock==1)
            return 0;
        else{
            file->sharedLock=1;
            return 1;
        }
    }
}