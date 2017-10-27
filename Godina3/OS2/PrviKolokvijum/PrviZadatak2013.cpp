const int timesliceHP = ..., timesliceMP = ..., timesliceLP = ...;
enum Queue {HP,MP,LP};
extern PCB* const idle;

class Scheduler {
public:
    Scheduler ();
    PCB* get ();
    void put (PCB*, int wasBlocked);
private:
    PCB *first_[3] = {0}, *last[3] = {0};
};

PCB* Scheduler::get (){
    PCB* ret=idle;
    for(int i=0; i<3; i++){
        if(first[i]!=nullptr){
            ret=first[i];
            first[i]=ret->next;
            if(first[i]==nullptr){
                last[i]=nullptr;
            }
            if(i==0){
                ret->timeslice=timesliceHP;
                ret->lastQueue=HP;
            }
            else if(i==1){
                ret->timeslice=timesliceMP;
                ret->lastQueue=MP;
            }
            else {
                ret->timeslice=timesliceLP;
                ret->lastQueue=LP;
            }
            return ret;
        }
    }
    return ret;
}

void Scheduler::put (PCB* pcb, int wasBlocked){
    int i=0;
    if(!wasBlocked) 
        if(pcb->lastQueue==HP) i=1;
        else i=2;

    if(first[i]==nullptr)
        first[i]=pcb;
    else
        last->next=pcb;
    last=pcb;
    pcb->next=nullptr;
}