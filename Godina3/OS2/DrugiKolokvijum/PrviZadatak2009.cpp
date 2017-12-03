// Zadatak 1, 2009

typedef unsigned int PID;  // Process ID
typedef unsigned long int PgID;   // page number
typedef unsigned long int FID;    // frame number

class FramePool {
public:
  FramePool () : head(0), tail(0) {}
  int  getFrame (PID proc, PgID page, FID& frame);
  void addFrame (PID proc, PgID page);
private:
  struct FPElem {
    PID proc;
    PgID page;
    FID frame;
    FPElem *prev, *next;
  };
  FPElem *head, *tail;
};

int  FramePool::getFrame (PID proc, PgID page, FID& frame){
  FPElem* curr=head;

  while(curr!=nullptr){
    if(curr->proc == proc && curr->page == page){
      frame=curr->frame;
      return 1;
    }
    curr=curr->next;
  }

  if(head != nullptr){
    frame=head->frame;
    return 0;
  }

  return -1;
}
