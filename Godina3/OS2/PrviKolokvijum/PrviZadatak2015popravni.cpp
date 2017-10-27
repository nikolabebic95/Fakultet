class Scheduler {
private:
    PCB* first_active_=nullptr, last_active_=nullptr;
    PCB* first_passive_=nullptr, last_passive_=nullptr;
public:
    Scheduler ();
    PCB* get ();
    void put (PCB* pcb, int wasBlocked);
};

PCB* Scheduler::get (){
    PCB* ret=first_active_;
    first_active_=ret->next;
    if(first_active_==nullptr){
        first_active_=first_passive_;
        last_active_=last_passive_;
        first_passive_=last_passive_=nullptr;
    }
}

void Scheduler::put (PCB* pcb, int wasBlocked){
    pcb->next=nullptr;
    if(wasBlocked){
        if(first_active_==nullptr)
            first_active_=pcb;
        else
            last_active_->next=pcb;
        last_active_=pcb;
    }
    else{
        if(first_passive_==nullptr)
            first_passive_=pcb;
        else
            last_passive_->next=pcb;
        last_passive_=pcb;
    }
}
