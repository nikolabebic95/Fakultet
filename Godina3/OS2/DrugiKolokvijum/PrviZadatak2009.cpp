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
  FPElem* tek=head;

  while(tek!=nullptr){
    if(tek->proc == proc && tek->page == page){
      frame=tek->frame;
      return 1;
    }
    tek=tek->sled;
  }

  if(head != mullptr){
    frame=head->frame;
    return 0;
  }

  return -1;
}
