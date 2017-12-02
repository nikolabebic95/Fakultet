// Zadatak 3, 2016

typedef unsigned long ulong;
typedef unsigned int RefBitReg;
const long RefBitTableSize0 = ..., RefBitTableSize1 = ...;
const unsigned short NumOfHistoryBits = ...; // A small positive value
typedef RefBitReg RefBitsTable1[RefBitTableSize1];
typedef RefBitsTable1* RefBitsTable[RefBitTableSize0];

ulong getWorkingSetSize (PCB* pcb){
    int counter=0;
    unsigned int mask=0;

    for(int i=0; i<NumOfHistoryBits; i++){
        mask<<=1;
        mask++;
    }
    mask<<=sizeof(unsigned int)*8-NumOfHistoryBits;

    for(int i=0; i<RefBitTableSize0; i++){
        RefBitsTable1* table=(pcb->refBits)[i];
        if(table!=nullptr){
            for(int j=0; j<RefBitTableSize1; j++){
                if (table[j] & mask) counter++;
            }
        }
    }
    return counter;
}