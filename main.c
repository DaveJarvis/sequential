/* ***********************************************************************
 *
 * Generates and evaluates a random expression.
 *
 * https://arxiv.org/pdf/1302.1479.pdf
 *
 * ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "split.h"
#include "random.h"
#include "eval.h"

/* Write the expression that equals this value to standard output. */
#define DEFAULT_GOAL 10958

/* Set of digits used to generate equations, in order given. */
#define DEFAULT_DIGITS "123456789"

/* Number of operators (size of OPERATORS). */
#define SIZEOF_OPERATORS 5

/* Number of bits to use when evaluating expressions. */
#define DEFAULT_PRECISION 2048

/* Non-terminals. */
const char *OPERATORS[ SIZEOF_OPERATORS ] = {
  "+",
  "-",
  "*",
  "^",
  "/"
};

/* Final expression size (9 terminals, 9 operators, 18 spaces, and padding). */
#define MAX_EXPR_LENGTH 64

/**
 * Build a random postfix expression.
 */
void generate_expression( char expr[ MAX_EXPR_LENGTH ], const char *set ) {
  /* Contains a randomly split set of numbers. */
  char buffer[ MAX_EXPR_LENGTH * 2 ];

  /* Total number of operations to perform (at least one). */
  unsigned int operations = rnd() % (strlen( set ) - 1) + 1;

  /* Nuke the previous expression. */
  memset( expr, 0, MAX_EXPR_LENGTH );

  /* Clear out the buffer before splitting digits into numbers. */
  memset( buffer, 0, MAX_EXPR_LENGTH * 2 );

  /* Slice and dice the digits in the given set into random lengths. */
  split( set, buffer, operations );

  /* Used to concatenate the individual numbers into the expression. */
  char *number = strtok( buffer, " " );

  /* Every expression must start with two numbers and this is the first. */
  strcat( expr, number );
  strcat( expr, " " );

  /* The tally of numbers must be one more than the number of operations. */
  while( operations > 0 ) {
    /* On the first iteration this will be the second number. */
    number = strtok( NULL, " " );

    /* Insert a number between the operators. */
    if( number != NULL ) {
      strcat( expr, number );
      strcat( expr, " " );
    }

    /* If an operator isn't inserted, then retain the operations count for
     * another iteration. This ensures the numbers will mix in across
     * all possible positions, presuming a uniform random number generator. */
    if( rnd() % 2 ) {
      /* Append a random operator. */
      strcat( expr, OPERATORS[ rnd() % SIZEOF_OPERATORS ] );
      strcat( expr, " " );

      operations--;
    }
  }
}

/**
 * Called to seed the randomness and initialize any libraries.
 */
void init( void ) {
  srand( time( NULL ) );

  /* Set default precision for the calculations. */
  mpfr_set_default_prec( (mpfr_prec_t)DEFAULT_PRECISION );
}

/**
 * Generates expressions, evaluates them, and then terminates if the result
 * is equal to the goal.
 */
int main( int c, char **v ) {
  char expr[ MAX_EXPR_LENGTH ];
  double goal = c >= 2 ? atof( v[1] ) : DEFAULT_GOAL;
  char *digits = c == 3 ? v[2] : DEFAULT_DIGITS;
  double result = -1;

  init();

  while( result != goal ) {
    generate_expression( expr, digits );
    result = evaluate_expression( expr );

    /* Show the expression that generates the goal value. */
    if( result == goal ) {
      printf( "%s= %f\n", expr, result );
    }
    else if( (result > goal && result < goal + 1) ||
             (result < goal && result > goal - 1)) {
      printf( "%s= %f (CLOSE)\n", expr, result );
    }
  }

  return 0;
}

