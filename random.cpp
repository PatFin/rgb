#include <stdlib.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include "rgb.h"

static volatile sig_atomic_t keepGoing = 1;

void handle_sigint(int s) {
  keepGoing = 0;
}

void handle_sigquit(int s) {
  RGB_reset();
}

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int main(int argc, char ** argv) {
  RGB_init();
  RGB_reset();

  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, handle_sigquit);
  
  srand(time(NULL));
  while(keepGoing) {
    int x = rand()%32;
    int y = rand()%32;
    int r = rand()%2;
    int g = rand()%2;
    int b = rand()%2;
    RGB_R[x][y]=Intensity[r];
    RGB_G[x][y]=Intensity[g];
    RGB_B[x][y]=Intensity[b];
    delay();
  }
  RGB_exit();
  return 0;
}
