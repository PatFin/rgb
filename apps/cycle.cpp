#include <signal.h>
#include <chrono>
#include <thread>

extern "C" {
#include "rgb.h"  
}

static int SHOW = 3;

static volatile sig_atomic_t keepGoing = 1;

void handle_sigint(int s) {
  keepGoing = 0;
}

void setUniformLevel(int color[32][32], int level){
  for(int i = 0; i < 32; i++) {
    for(int j=0; j < 32; j++){
      color[i][j] = level;
    }
  }
}

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(750));
}

int main(int argc, char ** argv) {
  RGB_init();

  signal(SIGINT,handle_sigint);
  signal(SIGQUIT, handle_sigint);

  while(keepGoing > 0) {
    int color = RGB_randColor();
    for (int i = 0; i < SHOW && keepGoing; i++) {
      setUniformLevel(RGB, color);
      delay();
      setUniformLevel(RGB, 0);
      delay();
    }
  }

  RGB_exit();
  return 0;
}
