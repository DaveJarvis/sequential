/* ***********************************************************************
 *
 * Generates cryptographically secure random numbers suitable for
 * simulations.
 *
 * ***********************************************************************/
#include "random.h"

#include <stdio.h>

/* Ensure ENTROPY is replenished first time around. */
int random_index = MAX_ENTROPY_SIZE;

/* Contains cryptographically secure truly random numbers. */
unsigned char ENTROPY[ MAX_ENTROPY_SIZE ];

/**
 * Compute a uniform random number between 0 and 255.
 */
unsigned char rnd() {
  if( random_index == MAX_ENTROPY_SIZE ) {
    /* Replenish the random buffer. */
    getrandom( ENTROPY, MAX_ENTROPY_SIZE, GRND_NONBLOCK );
    random_index = 0;
  }

  return ENTROPY[ random_index++ ];
}

