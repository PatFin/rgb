#include <stdlib.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include "rgb.h"

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
    int r = rand()%8;
    int g = rand()%4;
    int b = rand()%4;

    if (r >= 4){
      r = g = b = 0;
    }
    r = r%4;

    //Cascade the color
    for(int column = rand()%32, i=0, colorLimit = rand()%10;
	i < colorLimit && keepGoing == 1;
	i++, column = rand()%32) {
      
      for (int j=0; j<32 && keepGoing == 1;j++){
	RGB_R[column][j] = Intensity[r]; // (RGB_R[column][j] + r)%3;
	RGB_G[column][j] = Intensity[g]; //(RGB_G[column][j] + g)%3;
	RGB_B[column][j] = Intensity[b]; //(RGB_B[column][j] + b)%3;
	delay();
      }
    }
  }

  RGB_exit();
  return 0;
}
