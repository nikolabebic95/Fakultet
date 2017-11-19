unsigned fat[FATSIZE];
// svaki fajl ima ulancane blokove, on zna koji mu je prvi.
// poslednji blok u listi sadrzi 0. slobodni blokovi sadrze ~0u.

struct FCB{
    unsigned head;
    ...
}
unsigned extendFile (FCB* fcb, unsigned by){
    unsigned free_head=0;
    unsigned i, j=0;
    unsigned tek=0;

    for(i=0; i<by; i++){
        while(j<FATSIZE && fat[j]!=~0u){
            j++;
        }
        if(fat[j]==~0u){
            fat[j]=0;
            if(free_head==0)
                free_head=j;
            else
                fat[tek]=j;
            tek=j;
        }
        else
            break;
    }

    if(fcb->head==0)
        fcb->head=free_head;
    else{
        tek=fcb->head;
        while(fat[tek]!=0)
            tek=fat[tek];
        fat[tek]=free_head;
    }
    
    return i;
}