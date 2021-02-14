#include <stdlib.h>
#include <signal.h>
#include <chrono>
#include <thread>

extern "C" {
#include "rgb.h"
}

static volatile sig_atomic_t keepGoing = 1;

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void handle_sigint(int s) {
  keepGoing = 0;
}

int main(int argc, char ** argv) {
  RGB_init();

  signal(SIGINT, handle_sigint);
  srand(time(NULL));

  while(keepGoing) {
    //Choose a color
    int color = RGB_randColor();

    //Cascade the color
    for(int column = rand()%32, i=0, colorLimit = rand()%10;
        i < colorLimit && keepGoing == 1;
        i++, column = rand()%32) {
      for (int j=0; j<32 && keepGoing == 1;j++){
        RGB[column][j] = color;
        delay();
      }
    }
  }

  RGB_exit();
  return 0;
}
