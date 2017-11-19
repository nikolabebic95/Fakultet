unsigned long int owner;
unsigned long int group;
unsigned int protection;

UCB* getUCB (unsigned long int uid);

int isAllowed(FCB* file, unsigned long int uid, unsigned int op){
    op&=7;
    if(file==0)
        return 0;

    if(uid==file -> owner){
        if(file->protection & (op<<6))
            return 1;
        else
            return 0;
    }

    UCB* ucb=getUCB(uid);
    unsigned long int group=ucb->group;

    if(group==file->group){
        if(file->protection & (op<<3))
            return 1;
        else
            return 0;
    }

    if(file->protection & op)
        return 1;

    return 0;
}