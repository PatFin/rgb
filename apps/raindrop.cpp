#include <stdlib.h>
#include <signal.h>
#include <chrono>
#include <thread>

extern "C" { 
#include "rgb.h" 
}

const int DROP_COUNT = 70;
const int MIN_DROP_LENGTH = 4;
const int MAX_DROP_LENGTH = 10;
const int DELAY = 70; //milliseconds

static volatile sig_atomic_t keepGoing = 1;

struct drop {
  int column;
  int headRow;
  int length;
  int color;
} droplets[DROP_COUNT];

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
}

void handle_sigint(int s) {
  keepGoing = 0;
}

void initDrop(int idx) {
  droplets[idx].column=rand()%32;
  droplets[idx].color = RGB_randColor();
  droplets[idx].headRow=0 - rand()%20;
  droplets[idx].length = MIN_DROP_LENGTH + rand()%(MAX_DROP_LENGTH - MIN_DROP_LENGTH);
}

int main(int argc, char ** argv) {
  RGB_init();

  signal(SIGINT, handle_sigint);
  srand(time(NULL));


  for(int i = 0 ; i < DROP_COUNT; i++) {
    initDrop(i);
  }

  while(keepGoing) {
    for(int i=0;i<DROP_COUNT;i++){
      //Print the individual droplets and make them progress by one line
      int column = droplets[i].column;
      int headRow = droplets[i].headRow;
      int color = droplets[i].color;
      if (headRow >= 0 && headRow<32){
        RGB[column][headRow] = color;
      }

      int erase = headRow - droplets[i].length;
      if (erase >= 32) {
        initDrop(i);
      } else if (erase >= 0) {
        RGB[column][erase] = 0;
      }
      droplets[i].headRow++;
    }
    delay();
  }

  RGB_exit();
  return 0;
}
