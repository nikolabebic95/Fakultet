extern unsigned long fat[];
unsigned long freeHead;
struct FCB{
    unsigned long head;
    ...
}

unsigned long append(FCB* fcb){
    unsigned long free;
    unsigned long appIndex;

    if(freeHead==0)
        return 0;
    free=freeHead;
    freeHead=fat[freeHead];
    fat[free]=0;

    if(fcb->head==0)
        fcb->head=free;
    else{
        appIndex=fcb->head;
        while(fat[appIndex]!=0)
            appIndex=fat[appIndex];
        fat[appIndex]=free;
    }
    return free;
}