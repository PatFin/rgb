#include <wiringPi.h>
#include <stdint.h>
#include <chrono>
#include <thread>
#include <pthread.h>
#include "rgb.h"

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

/* 
 * Intensity level for each cell of the RGB matrix
 * Intensity level is determined by the number of bits
 * in the 8 bit value. 
 */
char RGB_R[32][32];
char RGB_G[32][32];
char RGB_B[32][32];

/* INTENSITY LEVELS FOR THE RGB */
char ZERO = 0;
char ONE = 5;
char TWO = 240;
char THREE = 255; 


char Intensity [4] = {ZERO, ONE, TWO, THREE}; //, FOUR, FIVE, SIX, SEVEN, EIGHT};

pthread_t refreshThread;
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
    digitalWrite(R1, RGB_R[line][x] > power);
    digitalWrite(G1, RGB_G[line][x] > power);
    digitalWrite(B1, RGB_B[line][x] > power);
    digitalWrite(R2, RGB_R[line+16][x] > power);
    digitalWrite(G2, RGB_G[line+16][x] > power);
    digitalWrite(B2, RGB_B[line+16][x] > power);

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
  std::this_thread::sleep_for(std::chrono::microseconds(2));
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
      RGB_R[i][j] = ZERO;
      RGB_G[i][j] = ZERO;
      RGB_B[i][j] = ZERO;
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
