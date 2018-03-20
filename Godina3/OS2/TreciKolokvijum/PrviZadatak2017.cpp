struct DiskRequest {
 DiskRequest *edfNext, *edfPrev;
 DiskRequest *scanNext, *scanPrev;
 long deadline;
 ...
};
class DiskScheduler {
public:
 DiskScheduler ();
 DiskRequest* get ();
 void put (DiskRequest*);
private:
 DiskRequest *edfHead, *scanHead;
};
DiskScheduler::DiskScheduler () : edfHead(0), scanHead(0) {}

DiskRequest* DiskScheduler::get(){
    if(edfHead == 0)
        return nullptr;

    DiskRequest* ret;

    if(edfHead->deadline <= 0)
        ret = edfHead;
    else
        ret = scanHead;

    if(edfHead == ret)
        edfHead = ret->edfNext;
    else
        ret->edfPrev->edfNext = ret->edfNext;
    if(ret->edfNext != nullptr)
        ret->edfNext->edfPrev = ret->edfPrev;

    if(ret->scanNext == ret)
        scanHead = nullptr;
    else{
        if(scanHead == ret)
            scanHead = ret->scanNext;
        ret->scanPrev->scanNext = ret->scanNext;
        ret->scanNext->scanPrev = ret->scanPrev;
    }
    return ret;
}