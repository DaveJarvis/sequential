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

/* 1 to write all expressions to standard error.
 * 0 to write only GOAL expression to standard output. */
#define DEBUG 0

/* Write the expression that equals this value to standard output. */
#define GOAL 10958

/* Number of operators (size of OPERATORS). */
#define SIZEOF_OPERATORS 5

/* Non-terminals. */
const char *OPERATORS[ SIZEOF_OPERATORS ] = {
  "+",
  "-",
  "*",
  "^",
  "/"
};

/* The number of digits constrains the total operations per expression. */
#define MAX_OPERATIONS 8

/* The minimum number of operations to use in a calculation. */
#define MIN_OPERATIONS 2

/* Final expression size (9 terminals, 9 operators, 18 spaces, and padding). */
#define MAX_EXPR_LENGTH 64

/**
 * Build a random postfix expression.
 */
void generate_expression( char expr[ MAX_EXPR_LENGTH ] ) {
  /* Contains a randomly split set of numbers. */
  char buffer[ MAX_EXPR_LENGTH * 2 ];

  /* Nuke the previous expression. */
  memset( expr, 0, MAX_EXPR_LENGTH );

  /* Total number of operations to perform (at least one). */
  unsigned int operations = rnd() % MAX_OPERATIONS + 1;

  /* Clear out the buffer before splitting digits into numbers. */
  memset( buffer, 0, MAX_EXPR_LENGTH * 2 );

  /* Slice and dice the digits into numbers of random lengths. */
  split( "123456789", buffer, operations );

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
    if( rnd() % 2 == 0 ) {
      /* Append a random operator. */
      strcat( expr, OPERATORS[ rnd() % SIZEOF_OPERATORS ] );
      strcat( expr, " " );

      operations--;
    }
  }
}

/**
 * 
 */
int main( int c, char **v ) {
  char expr[ MAX_EXPR_LENGTH ];
  double result = 0;

  srand( time( NULL ) );

  while( 1 ) {
    generate_expression( expr );
    result = evaluate_expression( expr );

    if( result == GOAL ) {
      printf( "%s = %f\n", expr, result );
      break;
    }
    else if( DEBUG ) {
      fprintf( stderr, "%s = %f\n", expr, result );
    }
  }

  return 0;
}

