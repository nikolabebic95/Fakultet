/*
 * Neki sistem primenjuje kontinualnu alokaciju memorije za procese. U strukturi PCB procesa
 * postoje sledeća polja:
 *  Word* mem_base: pokazivač na lokaciju u memoriji na kojoj je proces smešten; tip
 * Word predstavlja jednu adresibilnu jedinicu memorije;
 *  size_t mem_size: veličina memorijskog segmenta koju zauzima proces; size_t je
 * celobrojni tip za izražavanje veličina memorijskih segmenata, u jedinicama Word.
 * Sistemskim pozivom mem_extend proces može da traži povećanje svog memorijskog prostora
 * za traženu veličinu (proširenje iza kraja). Sistem će ispuniti ovaj zahtev ukoliko iza prostora
 * koji proces već zauzima postoji slobodan segment dovoljne veličine. U suprotnom, odbiće taj
 * zahtev (ne radi relokaciju procesa).
 * Slobodni segmenti ulančani su u listu, a funkcija
 * int mem_alloc(Word* address, size_t by);
 * pokušava da pronađe slobodan segment na adresi datoj prvim argumentom i da iz njega
 * alocira deo veličine date drugim argumentom. U slučaju uspeha, funkcija vraća 0. Ukoliko na
 * datoj adresi ne počinje slobodan segment ili on nije dovoljne veličine, ova funkcija vraća
 * negativnu vrednost (kod greške).
 * Korišćenjem već implementirane funkcije mem_alloc, implementirati funkciju
 * int mem_extend (PCB* p, size_t by);
 * koja se koristi u implementaciji opisanog sistemskog poziva mem_extend. Ova funkcija treba
 * da vrati 0 u slučaju uspeha, a negativnu vrednost u slučaju greške.
 */

typedef Word unsigned; /**< Data type for a memory word */

/**
 * \brief Struct representing a process context buffer
 */
 struct PCB{
    Word* mem_base; /**< Start address of the process */
    size_t mem_size; /**< Size of the process in words */
}

/**
 * \brief Tries to allocate given number of words at the given address
 * \param address Start address
 * \param words Number of words
 * \return Whether the allocation succeeded
 */
int mem_alloc(Word* address, size_t words);

/**
 * \brief Tries to extends memory allocated for process
 * \param p Pointer to the PCB
 * \param words Number of words
 * \return Whether the call was successful
 */
int mem_extend(PCB* p, size_t by){
    int flag=mem_alloc(p->mem_base + p->mem_size, by);
    if(!flag){
        p->mem_size+=by;
        return 0;
    }
    else
        return -1;
}
