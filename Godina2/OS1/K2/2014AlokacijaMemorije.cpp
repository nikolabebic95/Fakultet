/*Neki sistem primenjuje kontinualnu alokaciju memorije. Slobodni fragmenti dvostruko su
ulančani u listu na čiji prvi element ukazuje fmem_head. Svaki slobodni fragment predstavljen
je strukturom FreeMem koja je smeštena na sam početak tog slobodnog fragmenta:
struct FreeMem {
 FreeMem* next; // Next in the list
 FreeMem* prev; // Previous in the list
 size_t size; // Size of the free fragment
};
Implementirati funkciju
int mem_alloc(void* address, size_t by);
Ova funkcija pokušava da pronađe slobodan fragment na adresi datoj prvim argumentom i da
iz njega alocira deo veličine date drugim argumentom. Ukoliko na datoj adresi ne počinje
slobodan fragment ili on nije dovoljne veličine, ova funkcija vraća -1. Ukoliko na datoj adresi
postoji slobodan fragment dovoljne veličine, ova funkcija ažurira listu slobodnih framenata na
sledeći način:
 ukoliko bi iza alociranog dela preostao fragment koji je manji ili jednak veličini
strukture FreeMem, ceo taj slobodni fragment se alocira (ne ostavlja se ostatak koji je
premali za evidenciju) i izbacuje iz liste slobodnih;
 u suprotnom, preostali deo se ostavlja kao slobodan fragment.
U oba slučaja, funkcija vraća veličinu stvarno alociranog dela (veće ili jednako traženoj
veličini).*/

/**
 * \brief Struct representing a free memory block
 */
struct FreeMem{
    FreeMem* next; /**< Next fragment in the list */
    FreeMem* prev;  /**< Previous fragment in the list */
    size_t size; /**< Size of the free fragment */
}

extern FreeMem* fmem_head; /**< Head of the list */

/**
 * \brief Allocates fragment of given size at the given address
 * \param address Address of the fragment that should be allocated
 * \param by Size of the fragment that should be allocated in bytes
 */
int mem_alloc(void *address, size_t by){
    FreeMem *curr=fmem_head;
    while(curr!=nullptr){
        if(curr==address) break;
        curr=curr->next;
    }

    if(curr==nullptr || curr->size<by) return -1;

    FreeMem *prev=curr->prev;
    FreeMem *next=curr->next;
    size_t size=curr->size;

    if(sizeof(FreeMem) + by >= size){
        if(next)
            next->prev=prev;
        if(!prev)
            fmem_head=next;
        else
            prev->next=next;
        return size;
    }
    else{
        FreeMem *newFreeFrag=(FreeMem*)((char)curr+by);
        newFreeFrag->prev=prev;
        newFreeFrag->next=next;
        newFreeFrag->size=size-by;
        if(!prev)
            fmem_head=newFreeFrag;
        else
            prev->next=newFreeFrag;
        if(next)
            next->prev=newFreeFrag;
        return by;
    }
}