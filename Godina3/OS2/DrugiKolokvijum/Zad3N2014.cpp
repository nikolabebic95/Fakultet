// Zadatak 3, Nadoknada 2014

void incPageFaultCounter(PCB* pcb){
    if(pcb == 0) return;
    pcb->pageFaultCounters[pcb->pageFaultCursor]++;
}

void shiftPageFaultCounters(PCB* pcb){
    if(pcb == 0) return;
    pcb->pageFaultCursor = (pcb->pageFaultCursor + 1) % PFLTCOUNTERS;
    pcb->pageFaultCounters[pcb->pageFaultCursor] = 0;
}

unsigned getNumberOfPageFaults(PCB* pcb){
    if(pcb == 0) return;
    int sum = 0;
    for(int i=0; i<PFLTCOUNTERS; i++){
        sum += pcb->pageFaultCounters[i];
    }
    return sum;
}
