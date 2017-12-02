// Zadatak 2, Nadoknada 2013

void updateReferenceRegs (PCB* pcb){
    if(pcb == 0) return;

    for(int i=0; i<PMTSIZE; i++){
        unsigned int lru=pcb->pageRefHash.getValue(i);
        lru>>=1;

        if(pcb->pmt[i] & 1) lru |= ~((~0U) >> 1);

        pcb->pageRefHash.setValue(i, lru);
        pcb->pmt[i] &= ~1U;
    }
}