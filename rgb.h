#pragma once

/* 
 * Intensity level for each cell of the RGB matrix
 * Intensity level is determined by the number of bits
 * in the 8 bit value. 
 */
extern char RGB_R[][32];
extern char RGB_G[][32];
extern char RGB_B[][32];

/* INTENSITY LEVELS FOR THE RGB */
extern char ZERO;
extern char ONE;
extern char TWO;
extern char THREE; 
extern char FOUR;
extern char FIVE;
extern char SIX;
extern char SEVEN;
extern char EIGHT;

extern char Intensity [];

void RGB_init();

void RGB_reset();

void RGB_exit();
