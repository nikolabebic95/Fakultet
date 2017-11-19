struct PCB{
    char* mem_base_addr; // gde pocinje proces
    size_t mem_size; // broj bajtova koje zauzima
    PCB* mem_next; // sledeci pcb u listi
};

PCB* proc_mem_head;

char* user_proc_mem_start;
char* user_proc_mem_end;

struct FreeSegment {
    FreeSegment* next; // Next free segment in the list
    size_t size; // Total size of the free segment
};

FreeSegment* mem_free_head;

void mem_compact(){
    char* first_byte=user_proc_mem_start;
    PCB* curr_proc=proc_mem_head;

    while(curr_proc!=0){
        memcpy(first_byte, curr_proc->mem_base_addr, curr_proc->mem_size);
        curr_proc->mem_base_addr=first_byte;
        first_byte+=curr_proc->mem_size;
        curr_proc=curr_proc->mem_next;
    }

    mem_free_head=(FreeSegment*) first_byte;
    free->next=0;
    free->size=user_proc_mem_end-first_byte+1;
}