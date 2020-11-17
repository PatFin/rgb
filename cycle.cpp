#include <signal.h>
#include <chrono>
#include <thread>
#include "rgb.h"

static volatile sig_atomic_t keepGoing = 1;

void handle_sigint(int s) {
  keepGoing = 0;
}

void setUniformLevel(char color[32][32], char level){
  for(int i = 0; i < 32; i++) {
    for(int j=0; j < 32; j++){
      color[i][j] = level;
    }
  }
}

void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void cycleColor(char color[32][32]) {
  for(int idx = 0; idx<=3; idx++) {
    setUniformLevel(color, Intensity[idx]);
    delay();
    setUniformLevel(color, Intensity[0]);
    delay();
  }
  for(int idx = 2; idx>=1; idx--) {
    setUniformLevel(color, Intensity[idx]);
    delay();
    setUniformLevel(color, Intensity[0]);
    delay();
  }
  RGB_reset();
}

void cycleColor(char c1[32][32], char c2[32][32]) {
  for(int idx = 0; idx<=3; idx++) {
    setUniformLevel(c1, Intensity[idx]);
    setUniformLevel(c2, Intensity[idx]);
    delay();
    setUniformLevel(c1, Intensity[0]);
    setUniformLevel(c2, Intensity[0]);
    delay();
  }
  for(int idx = 2; idx>=1; idx--) {
    setUniformLevel(c1, Intensity[idx]);
    setUniformLevel(c2, Intensity[idx]);
    delay();
    setUniformLevel(c1, Intensity[0]);
    setUniformLevel(c2, Intensity[0]);
    delay();
  }
  RGB_reset();
}


void cycleColor() {
  for(int idx = 0; idx<=3; idx++) {
    setUniformLevel(RGB_B, Intensity[idx]);
    setUniformLevel(RGB_R, Intensity[idx]);
    setUniformLevel(RGB_G, Intensity[idx]);
    delay();
    setUniformLevel(RGB_B, Intensity[0]);
    setUniformLevel(RGB_R, Intensity[0]);
    setUniformLevel(RGB_G, Intensity[0]);
    delay();
  }
  for(int idx = 2; idx>=1; idx--) {
    setUniformLevel(RGB_B, Intensity[idx]);
    setUniformLevel(RGB_R, Intensity[idx]);
    setUniformLevel(RGB_G, Intensity[idx]);
    delay();
    setUniformLevel(RGB_B, Intensity[0]);
    setUniformLevel(RGB_R, Intensity[0]);
    setUniformLevel(RGB_G, Intensity[0]);
    delay();
  }
  RGB_reset();
}

int main(int argc, char ** argv) {
  RGB_init();

  signal(SIGINT,handle_sigint);
  
  while(keepGoing > 0) {
    //Cycle Red level
    cycleColor(RGB_R);
    if (!keepGoing) break;
    cycleColor(RGB_B);
    if (!keepGoing) break;
    cycleColor(RGB_G);
    if (!keepGoing) break;
    cycleColor(RGB_R,RGB_B);
    if (!keepGoing) break;
    cycleColor(RGB_G,RGB_B);
    if (!keepGoing) break;
    cycleColor(RGB_R,RGB_G);
  }
  
  RGB_exit();
  return 0;
}
