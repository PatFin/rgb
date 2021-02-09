#pragma once

/**
 * Intensity level for each cell of the RGB matrix
 * Intensity level is determined by the number of bits
 * in the 8 bit value. 
 */
extern int RGB[][32];

/** INTENSITY LEVELS FOR THE RGB */
#define ZERO 0
#define ONE  5
#define TWO  240
#define THREE  255

/** COLORS FOR THE RGB */
#define RED  (255 << 16)
#define GREEN (255 << 8)
#define BLUE  (255 << 0)

/**
 * Initialization method. Prepares a dedicated thread to send new data to the
 * LCD panel.
 */
void RGB_init();

/**
 * Clears the array of all colors, making the display completely blanck
 */
void RGB_reset();

/**
 * Cleanup procedure. This needs to be called before the program piloting the
 * panel terminated. 
 */
void RGB_exit();

/**
 * Helper method. Prepares a random color and returns it. The method is
 * programmed based on the rand() method but uses a mask to reduce the odds of
 * producing a white color. 
 */
int RGB_randColor();
