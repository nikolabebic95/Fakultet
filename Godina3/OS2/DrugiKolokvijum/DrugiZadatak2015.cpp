// Zadatak 2, 2015

struct PCB {
 ...
 unsigned int clockHand;
 unsigned int* pageCounters; // Page usage counters
 unsigned int* pageFifo; // Pointer to the FIFO page table
};

int getVictimPage(PCB* pcb){
    while(true){
        if(pcb->pageCounter[pcb->clockHand] > 0){
            (pcb->pageCounter[pcb->clockHand])--;
            pcb->clockHand=pcb->pageFifo[pcb->clockHand];
        }
        else{
            int ret=pcb->clockHand;
            pcb->clockHand=pcb->pageFifo[pcb->clockHand];
            return ret;
        }
    }
}