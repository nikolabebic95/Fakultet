// Zadatak 2, Nadoknada 2014

void updateReferenceRegs (PCB* pcb) {
 if (pcb==0) return; // Exception!
 for (unsigned page=0; page<PMTSIZE; page++) {
 unsigned frame = pcb->pmt[page];
 if (!frame) continue;
 unsigned ref = pcb->pageRefHash.getValue(page);
 ref >>= 1;
 if (frame&1) ref |= ~MAXINT;
 pcb->pageRefHash.setValue(page,ref);
 (pcb->pmt[page]) &= ~1U; // Reset the reference bit
 }
} 

unsigned getLRUPage (PCB* pcb){
    if(pcb == 0) return -1;

    int minVal=~0u, minIndex=-1;
    for(int i=0; i<PMTSIZE; i++){
        if(pmt[i] != 0 && (minIndex == -1 || minVal > pcb->pageRefHash.getValue(i))){
            minIndex=i;
            minVal=pcb->pageRefHash.getValue(i);
        }
    }

    return minIndex;
}
