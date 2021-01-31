#include <signal.h>
#include <chrono>
#include <thread>
#include "rgb.h"

#define B(x) S_to_binary_(#x)

static inline char S_to_binary_(const char *s)
{
  char i = 0;
  while (*s) {
    i <<= 1;
    i += *s++ - '0';
  }
  return i;
}

static int SHOW = 2;

static char INTENSITY = B(10101010);

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
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void cycleColor(char color[32][32]) {
  for(int idx = 0; idx<=SHOW; idx++) {
    setUniformLevel(color, INTENSITY);
    delay();
    setUniformLevel(color, Intensity[0]);
    delay();
  }
}

void cycleColor(char c1[32][32], char c2[32][32]) {
  for(int idx = 0; idx<=SHOW; idx++) {
    setUniformLevel(c1, INTENSITY);
    setUniformLevel(c2, INTENSITY);
    delay();
    setUniformLevel(c1, Intensity[0]);
    setUniformLevel(c2, Intensity[0]);
    delay();
  }
}


void cycleColor() {
  for(int idx = 0; idx<=SHOW; idx++) {
    setUniformLevel(RGB_B, INTENSITY);
    setUniformLevel(RGB_R, INTENSITY);
    setUniformLevel(RGB_G, INTENSITY);
    delay();
    setUniformLevel(RGB_B, Intensity[0]);
    setUniformLevel(RGB_R, Intensity[0]);
    setUniformLevel(RGB_G, Intensity[0]);
    delay();
  }
}

int main(int argc, char ** argv) {
  RGB_init();

  signal(SIGINT,handle_sigint);
  signal(SIGQUIT, handle_sigint);
  
  while(keepGoing > 0) {
    cycleColor();
    if (!keepGoing) break;
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
