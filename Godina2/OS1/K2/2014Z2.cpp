FreeMem *free_mem_head;

struct FreeMem {
 FreeMem* next; // Next in the list
 FreeMem* prev; // Previous in the list
 size_t size; // Size of the free fragment
};

int mem_alloc(void* address, size_t by){
    FreeMem* curr=free_mem_head;
    while(curr!=null && curr!=address)
        curr=curr->next;

    if(curr==null || curr->size<by) return -1;

    size_t ret;
    if(curr->size<=sizeof(FreeMem)+by){
        ret=curr->size;
        if(free_mem_head==curr)
            free_mem_head=curr->next;
        else
            curr->prev->next=curr->next;
        if(curr->next)
            curr->next->prev=curr->prev;
    }
    else{
        ret=by;
        FreeMem* next=curr->next;
        FreeMem* prev=curr->prev;
        size_t size;

        FreeMem* new_elem=((FreeMem*)((char*)curr+by);
        new_elem->next=next;
        new_elem->prev=prev;
        new_elem->size=size-by;

        if(free_mem_head==curr)
            free_mem_head=new_elem;
        else
            new_elem->prev->next=new_elem;
        if(new_elem->next)
            new_elem->next->prev=new_elem;
    }
    return ret;
}