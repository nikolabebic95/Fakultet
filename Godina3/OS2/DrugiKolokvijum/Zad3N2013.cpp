// Zadatak 3, Nadoknada 2013

template <class T, int slabSize>
class SlabAllocator {
public:
 SlabAllocator ();
 void* alloc ();
 void free (void*);
private:
 struct Slot {
 char slot[sizeof(T)];
 int isFree;
 Slot () : isFree(1) {}
 };
 static const int numOfSlots = (slabSize-2*sizeof(Slab*))/sizeof(Slot);
 struct Slab {
 Slot slots[numOfSlots];
 Slab *next, *prev;
 void* operator new (size_t) { return BuddyAllocator::alloc(slabSize); }
 void operator delete (void* p) { BuddyAllocator::free(p,slabSize); }
 };
 Slab *cacheHead, *cacheTail;
};
template<class T, int slabSize>
SlabAllocator<T,slabSize>::SlabAllocator () {
 cacheHead = cacheTail = new Slab();
}

template<class T, int slabSize>
void* SlabAllocator<T,slabSize>::alloc(){
    Slab* curr=cacheHead;

    while(curr){
        for(int i=0; i<numOfSlots; i++){
            if(curr->slots[i].isFree){
                curr->slots[i].isFree=0;
                return &(curr->slots[i].slot);
            }

        }
        curr=curr->next;
    }

    Slab* newSlab=new Slab();

    newSlab->next=cacheHead;
    newSlab->prev=nullptr;
    if(cacheHead != nullptr)
        cacheHead->prev = newSlab;
    else
        cacheTail=newSlab;
    cacheHead=newSlab;

    newSlab->slots[0].isFree=0;
    return &(newSlab->slots[0].slot);
}