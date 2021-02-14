#include <wiringPi.h>
#include <stdint.h>
#include <chrono>
#include <thread>
#include <pthread.h>

extern "C" {
  #include "rgb.h"
}



#define A 22
#define B 26
#define C 27
#define D 20

#define R1 5
#define G1 13
#define B1 6
#define R2 12
#define G2 16
#define B2 23

#define CLK 17
#define LAT 21
#define OE 4

/**
 * Intensity level for each cell of the RGB matrix
 * Intensity level is determined by the number of bits
 * in the 8 bit value.
 * The 32 bit number contained in here is used as follows:
 * [________ RRRRRRRR GGGGGGGG BBBBBBBB]
 */
int RGB[32][32];

/**
 * Thread in charge of actionning the GPIO to send the contents of #RGB to the
 * panel
 */
pthread_t refreshThread;

/** Flag used to signal to the refreshThread that is needs to quit */
volatile bool RGB_exitFlag;

/* Forward declaration of procedures */ 
void * refresh_thread(void * arg);

void RGB_init(){
  //Initialize wiringPi library
  wiringPiSetupGpio();

  //Set the necessary pins to write mode
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(OE, OUTPUT);

  //Reset the matrix
  RGB_reset();
  digitalWrite(OE, 0);

  //Launch the pthread responsible for refreshing the RGB matrix
  RGB_exitFlag = false;
  pthread_create(&refreshThread, NULL, refresh_thread, NULL);
}

void RGB_refresh(){
  static int line = 0;
  static uint8_t power = 0;

  for(int x = 0; x < 32; x++) {
    int cell1 = RGB[line][31-x];
    int cell2 = RGB[line+16][31-x];

    digitalWrite(R1, ((cell1 & 16711680) >> 16) > power);
    digitalWrite(G1, ((cell1 & 65280) >> 8) > power);
    digitalWrite(B1, (cell1 & 255) > power);

    digitalWrite(R2, ((cell2 & 16711680) >> 16) > power);
    digitalWrite(G2, ((cell2 & 65280) >> 8) > power);
    digitalWrite(B2, (cell2 & 255) > power); 

    //    digitalWrite(R1, RGB_R[x][line] > power);
    //digitalWrite(G1, RGB_G[x][line] > power);
    //digitalWrite(B1, RGB_B[x][line] > power);
    //digitalWrite(R2, RGB_R[line+16][x] > power);
    //digitalWrite(G2, RGB_G[line+16][x] > power);
    //digitalWrite(B2, RGB_B[line+16][x] > power);

    digitalWrite(CLK, 1);
    digitalWrite(CLK, 0);
  }
  digitalWrite(OE, 1);

  digitalWrite(LAT, 1);
  digitalWrite(LAT, 0);

  //Write the ABCD address
  digitalWrite(A, line & 1);
  digitalWrite(B, line & 2);
  digitalWrite(C, line & 4);
  //For D, first write the opposite value then flip output
  digitalWrite(D, line < 8? 1 : 0);
  std::this_thread::sleep_for(std::chrono::microseconds(1));
  digitalWrite(D, line < 8? 0 : 1);

  digitalWrite(OE, 0);
  line++;
  if (line >= 16) {
    line = 0;
    power = (power + 1) % 8;
  }
}

void * refresh_thread(void * arg){
  while(!RGB_exitFlag) {
    RGB_refresh();
    std::this_thread::sleep_for(std::chrono::microseconds(6));
  }
  return NULL;
}


void RGB_reset(){
  for(int i = 0; i < 32; i++) {
    for(int j=0; j < 32; j++){
      RGB[i][j] = ZERO;
    }
  }
}

void RGB_exit() {
  RGB_exitFlag = true;
  pthread_join(refreshThread, NULL);

  RGB_reset();
  for (int i = 0; i < 16; i++) {
    RGB_refresh();
  }
  digitalWrite(OE, 1);
}


int RGB_randColor() {
  int colorMask = 5;
  int mask = (colorMask << 16) | (colorMask << 8) | (colorMask);
  return rand() & mask;
}
