typedef uint unsigned int;
struct FreeFrameDescr {
 ushort isSlotFree; // Is this slot in the pool's array free?
 uint frame; // The frame referenced by this descriptor
 uint pid; // PID of the process that owned (released) this frame
 uint page; // The page of the process that owned this frame
};
FreeFrameDescr freeFramePool[FreeFramePoolSize]; // The pool

int getFreeFrame (uint pid, uint page, uint* frame){
    FreeFrameDescr* curr, first;
    bool firstFound=false;

    for(int i=0; i<FreeFramePoolSize; i++){
        curr=&freeFramePool[i];
        if(curr->isSlotFree){
            if(curr->pid == pid && curr->page == page){
                curr->isSlotFree=false;
                *frame=curr->frame;
                return 1;
            }
            else{
                if(firstFound==false){
                    firstFound=true;
                    first=curr;
                }
            }
        }
    }

    if(firstFound==false)
        return -1;

    first->isSlotFree=false;
    *frame=first->frame;
    return 0;
}
