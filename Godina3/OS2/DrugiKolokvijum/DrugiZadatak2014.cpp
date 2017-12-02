// Zadatak 2, 2014

struct PCB {
 ...
 unsigned int clockHand;
 unsigned long* pmt; // Pointer to the PMT
 unsigned int* pagefifo; // Pointer to the FIFO page table
};

int findBestCandidate (PCB* pcb, unsigned int modifyBit){
    if(pcb == 0) return -1;

    unsigned long mask=0;
    for(int i=0; i<sizeof(unsigned long)*8; i++){
        mask<<=1;
        mask++;
    }
    mask-=2;

    //mask = ~2;

    unsigned int first = pcb->clockHand;
    bool f=true;

    while((pcb->clockHand == first && f==true) || pcb->clockHand != first){
        f=false;

        if((pcb->pmt[pcb->clockHand] & 1) == modifyBit){
            if(pcb->pmt[pcb->clockHand] & 2){
                pcb->pmt[pcb->clockHand] &= mask;
            }
            else{
                return 1;
            }
        }

        pcb->clockHand=next(pcb->clockHand);
    }

    return 0;
}
