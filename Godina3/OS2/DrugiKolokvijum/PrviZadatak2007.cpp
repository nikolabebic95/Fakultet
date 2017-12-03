// Zadatak 1, 2007

const int num_of_pages = ...; // number of pages in one address space
typedef unsigned int page_descr;  // page descriptor is one word
typedef page_descr* PMT;   // PMT is an array of page_descr

typedef unsigned int lru_reg;
typedef lru_reg* LRU_regs_table; // LRU table is an array of lru_reg

int is_in_mem(page_descr);

void update_lru_regs (PMT pmt, LRU_regs_table lru){
  for(int i=0; i<num_of_pages; i++){
    if(is_in_mem(pmt[i])){
      page_descr mask = ~((~0U)>>1);
      lru[i]>>=1;
      lru[i]|=pmt[i] & mask;      
    }
  }
}

int get_victim(PMT pmt, LRU_regs_table lru){
  page_descr min=~0U;
  int idx = -1;
  for(int i=0; i<num_of_pages; i++){
    if(is_in_mem(pmt[i])){
      if(lru[i] < min || idx == -1){
        min=lru[i];
        idx=i;
      }
    }
  }

  return idx;
}
