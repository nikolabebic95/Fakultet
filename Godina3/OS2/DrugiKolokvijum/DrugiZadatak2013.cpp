// Zadatak 2, 2013

struct PCB {
 ...
 unsigned int clockHand;
 unsigned long* pmt; // Pointer to the PMT
 unsigned int* pagefifo; // Pointer to the FIFO page table
};

int findBestCandidate (PCB* pcb, unsigned int modifyBit);

unsigned int getVictimPage(PCB* pcb){
    if(pcb == nullptr)
        return -1;

    int victim;

    if(findBestCandidate(pcb, 0) != -1){
        victim=pcb->clockHand;
        pcb->clockHand=pcb->pagefifo[pcb->clockHand];
        return victim;
    }
    if(findBestCandidate(pcb, 1) != -1){
        victim=pcb->clockHand;
        pcb->clockHand=pcb->pagefifo[pcb->clockHand];
        return victim;
    }
    if(findBestCandidate(pcb, 0) != -1){
        victim=pcb->clockHand;
        pcb->clockHand=pcb->pagefifo[pcb->clockHand];
        return victim;
    }
    if(findBestCandidate(pcb, 1) != -1){
        victim=pcb->clockHand;
        pcb->clockHand=pcb->pagefifo[pcb->clockHand];
        return victim;
    }

    return -1;
}
