struct DiskRequest{
    unsigned int cyl;
    DiskRequest* prev;
    DiskRequest* next;
}

class DiskScheduler {
public:
    DiskScheduler (){}
    DiskRequest* get ();
    void put (DiskRequest*);
private:
    DiskRequest* head = nullptr;
    DiskRequest* curr = nullptr;
};

DiskRequest* DiskScheduler::get(){
    DiskRequest* ret;
    if(head == nullptr)
        return nullptr;
    if(curr == nullptr)
        curr = head;

    ret = curr;
    if(curr->prev == nullptr)
        head = curr->next;
    else
        curr->prev->next = curr->next;
    if(curr->next != nullptr)
        curr->next->prev = curr->prev;
    curr = curr->next;

    return ret;
}

void DiskScheduler::put(DiskRequest* request){
    DiskRequest* prev = nullptr;
    DiskRequest* curr = head;

    while(curr!=nullptr && curr->cyl < request->cyl){
        prev = curr;
        curr = curr->next;
    }

    request->prev = prev;
    request->next = curr;

    if(prev == nullptr)
        head = request;
    else
        prev->next = request;
    if(curr != nullptr)
        curr->prev = request;
}
