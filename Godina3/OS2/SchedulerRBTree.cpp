//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2 Scheduler
//  Multi-level queue
//  Implementacija preko crveno-crnog stabla (std::map)
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  U nekom sistemu klasa Scheduler, čiji je interfejs dat dole, implementira raspoređivač
//  spremnih procesa po prioritetu (engl. priority scheduling). Implementirati ovu klasu tako da i
//  operacija dodavanja novog spremnog procesa put() i operacija uzimanja spremnog
//  procesa koji je na redu za izvršavanje get() budu ograničene po vremenu izvršavanja
//  vremenom koje ne zavisi od broja spremnih procesa (kompleksnost O(1)). Između premnih
//  procesa sa istim prioritetom raspoređivanje treba da bude FCFS. Konstanta MAXPRI je
//  maksimalna vrednost prioriteta (prioriteti su u opsegu 0..MAXPRI, s tim da je 0 najviši
//  prioritet). U slučaju da nema drugih spremnih procesa, treba vratiti proces na koga ukazuje
//  idle (to je uvek spreman proces najnižeg prioriteta). U strukturi PCB polje priority tipa
//  int predstavlja prioritet procesa, a polje next pokazivač tipa PCB* koji služi za ulančavanje
//  struktura PCB u jednostruke liste. 
// 
//==========================================================================================================//
//==========================================================================================================//
//
//  Rešenje sa sajta pravi niz pokazivača na liste za svaki mogući prioritet.
//  To nije dobro ako prioriteta ima mnogo, jednostvno mnogo memorije ćemo potrošiti na prazne pokazivače
//  Rešenje je da umesto niza i to ulančavamo u listu, tako da imamo list-of-lists za PCB-ove.
//  Pošto ova lista mora da bude sortirana po prioritetu, optimizacija koja ima smisla je da zapravo to
//  i ne bude lista, nego neko binarno stablo pretraživanja. Crveno crno stablo postoji implementirano
//  u STL, kao std::map, i to možemo iskoristiti za rešavanje ovog zadatka.
//
//==========================================================================================================//
//==========================================================================================================//

#include <list>
#include <map>

#include "pcb.h"

const int MAXPRI = ...;
extern PCB* idle;

class Scheduler {
public:
    Scheduler() {}
    PCB* get();
    void put(PCB*);

private:
    std::map<int, std::list<PCB*>> multi_level_queue_;

};

PCB *Scheduler::get() {
    
    // Ako ne postoji nijedan proces u raspoređivaču, vraćamo idle
    if (multi_level_queue_.empty()) return idle;

    // Pronađemo FCFS listu procesa sa najboljim prioritetom
    auto best_list_iterator = multi_level_queue_.begin();
    auto best_list = best_list_iterator->second;
    
    // Izvadimo prvi proces iz liste
    auto ret = best_list.front();
    best_list.pop_front();

    // Proverimo da li je lista ostala prazna, i ako jeste, izbacimo je iz stabla
    if (best_list.empty()) multi_level_queue_.erase(best_list_iterator);

    return ret;
}

void Scheduler::put(PCB *pcb) {
    // Jednostavno, ubacimo proces na kraj liste za njegov prioritet
    // U slučaju da ta lista trenutno ne postoji, operator[] će instancirati praznu listu
    multi_level_queue_[pcb->priority].push_back(pcb);
}
