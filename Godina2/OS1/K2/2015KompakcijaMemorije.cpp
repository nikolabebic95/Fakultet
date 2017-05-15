/* 
 * U nekom sistemu koristi se kontinualna alokacija memorije. U PCB postoje sledeća polja:
 * • char* mem_base_addr: početna adresa u memoriji na koju je smešten proces;
 * • size_t mem_size: veličina dela memorije koju zauzima proces;
 * • PCB* mem_next: pokazivač na sledeći u listi procesa; PCB procesa su ulančani u ovu
 * listu po redosledu njihovog smeštanja u memoriji (po rastućem redosledu
 * mem_base_addr); glava ove liste je globalna promenljiva proc_mem_head.
 * Na početak dela operativne memorije koja se koristi za smeštanje procesa ukazuje pokazivač
 * user_proc_mem_start, a na njegov kraj (na poslednji znak) pokazivač user_proc_mem_end;
 * oba su tipa char*.
 * Fragmenti slobodne memorije ulančani su u jednostruko ulančanu listu, pri čemu se svaki
 * element te liste, tipa FreeSegment, smešta na sam početak slobodnog fragmenta. Glava ove
 * liste je u globalnoj promenljivoj mem_free_head. Struktura FreeSegment izgleda ovako:
 * struct FreeSegment {
 *     FreeSegment* next; // Next free segment in the list
 *     size_t size; // Total size of the free segment
 * };
 * Napisati proceduru mem_compact() koja vrši kompakciju slobodnog prostora relokacijom
 * procesa. 
 */

/**
 * \brief Struct representing a process context buffer
 */
struct PCB{
    char *mem_base_addr; /**< Start address of the process */
    size_t mem_size; /**< Size of the process in bytes */
    PCB *mem_next; /**< Next process context buffer */
};

PCB *proc_mem_head; /**< Head of the PCBs list */

char *user_proc_mem_start; /**< First address in the memory */
char *user_proc_mem_end; /**< Last address in the memory */

/**
 * \brief Struct representing a free segment of memory
 */
struct FreeSegment{
    FreeSegment *next;/**< Next free segment */
    size_t size; /**< size of the free segment */
};

FreeSegment *mem_free_head; /**< Head of the free segments list */

/**
 * \brief Compresses memory used for processes
 */
void mem_compact(){
    char* currSegment=user_proc_mem_start;
    PCB* currPCB=proc_mem_head;

    while(currPCB!=nullptr){}
        if(currPCB->mem_base_addr!=currSegment){
            memcpy(currSegment, currPCB->mem_base_addr, mem_size);
            currPCB->mem_base_addr=currSegment;
        }

        currSegment=currSegment+currPCB->size;
        currPCB=currPCB->next;
    }

    mem_free_head=(FreeSegment)currSegment;
    mem_free_head->next=nullptr;
    mem_free_head->size=user_proc_mem_end+1-(char*)mem_free_head;
}
