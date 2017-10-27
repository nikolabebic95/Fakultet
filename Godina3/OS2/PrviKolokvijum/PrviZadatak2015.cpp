class Scheduler {
public:
 Scheduler ();
 PCB* get ();
 void put (PCB*);
private:
 PCB* first[N], last[N];
 static unsigned thresholds[N];
 static const int N;
 ...
};

Scheduler::Scheduler(){
    for(int i=0; i<N; i++){
        first[i]=nullptr;
        last[i]=nullptr;
    }
}

void Scheduler::put (PCB* pcb){
    for(int i=0; i<N; i++){
        if (pcb->tau<=tresholds[i] || i==(N-1){
            if(first[i]==nullptr){
                first[i]=pcb;
            }
            else{
                last[i]->next=pcb;
            }
            pcb->next=nullptr;
            last[i]=pcb;
            return;
        }
    }
}

PCB* Scheduler::get (){
    PCB* ret=0;
    for(int i=0; i<n; i++){
        if(first[i]!=nullptr){
            ret=first[i];
            first[i]=ret->next;
            if(first[i]==nullptr)
                last[i]=nullptr;
        }
    }
    return ret;
}