// Zadatak 3, 2014

const int N = ...;
#define page_align(ptr) ...
extern void free(void*);
struct Slot { // Header stored in a free slot
 Slot *prev, *next; // Next and previous free slot in the same slab
};
struct Slab { // Header of each slab
 unsigned int freeSlots; // Number of free slots in this slab
 Slab *prev, *next; // Next and previous slab in the same cache
 Slot *head, *tail; // Free slots in this slab
};
struct Cache {
 Slab *head, *tail; // List of all slabs in this cache
};

int slab_free_slot (Cache* cache, void* slot){
    if(slot == nullptr || cache == nullptr)
        return -1;

    Slot* pSlot=(Slot*)slot;
    Slab* slab=(Slab*)page_align(slot);

    pSlot->prev=0;
    pSlot->next=slab->head;
    if(slab->head != nullptr)
        slab->head->prev=pSlot;
    slab->head=pSlot;

    slab->freeSlots++;

    if(slab->freeSlots == N){
        if(cache->head == slab)
            cache->head = slab->next;
        else
            slab->prev->next=slab->next;
        if(cache->tail == slab)
            cache->tail = slab->prev;
        else
            slab->next->prev=slab->prev;

        free(slab);
    }

    return 1;
}
