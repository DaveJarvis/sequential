/* ***********************************************************************
 *
 * Splits an arbitrarily long string into a space-separated tokenized
 * string. The length of each token is random.
 *
 * ***********************************************************************/
#include "split.h"
#include "random.h"

#define FALSE 0
#define TRUE !FALSE

/**
 * Split a set of characters into randomly-sized parts. Calling function
 * must initialize result.
 *
 * @param s The set of characters to split.
 * @param result The memory location for the split results (must be zero).
 * @param n The number of subsets to create.
 */
void split( char *s, char *result, int n ) {
  int l = strlen( s ) - 1;
  int space_holders[ l ];

  /* Faster ways to smite the old data? */
  for( int i = 0; i < l; i++ ) {
    space_holders[ i ] = TRUE;
  }

  /* Generate n random groups. */
  for( int spaces = n; spaces > 0; spaces-- ) {
    do {
      unsigned int r = rnd() % l;

      /* Eventually all place holders for spaces will be filled. */
      if( space_holders[ r ] ) {
        space_holders[ r ] = FALSE;
        break;
      }
    }
    while( 1 );
  }

  /* Generate the result by injecting spaces into precalculated places. */
  for( int i = 0; i < l; i++ ) {
    *result = s[ i ];
    result++;

    if( !space_holders[ i ] ) {
      *result = ' ';
      result++;
    }
  }

  /* The last character. */
  *result = s[l];
}

