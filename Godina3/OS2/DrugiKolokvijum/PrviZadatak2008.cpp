// Zadatak 1, 2008

typedef unsigned int page_descr;  // page descriptor is one word
typedef page_descr* PMT;   // PMT is an array of page_descr

int get_clock_frame();
void move_clock_hand();
page_descr* get_owner_page(int frame_num);

int get_victim_frame(){
  while(true){
    int frame=get_clock_frame();
    page_descr* frameD=get_owner_page(frame);
    if(page_descr == 0) {
      return frame;
    }
    if(*page_descr & 1){
      *page_descr &= ~1;
      move_clock_hand();
    }
    else{
      return frame;
    }
  }
}