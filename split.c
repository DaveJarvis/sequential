/* ***********************************************************************
 *
 * Splits an arbitrarily long string into a space-separated tokenized
 * string. The length of each token is random.
 *
 * ***********************************************************************/
#include "split.h"
#include "random.h"

/**
 * Split a set of characters into randomly-sized parts. The result must
 * be initialized to zero before calling this function.
 *
 * @param s The set of characters to split.
 * @param result The memory location for the split results (must be zero'd).
 * @param n The number of subsets to create.
 */
void split( const char *s, char *result, int n ) {
  int l = strlen( s ) - 1;
  int space_holders[ l ];

  /* Faster ways to smite the data? */
  for( int i = 0; i < l; i++ ) {
    space_holders[ i ] = TRUE;
  }

  /* Generate n random groups. */
  for( int spaces = n; spaces > 0; spaces-- ) {
    do {
      unsigned int r = rnd() % l;

      /* Eventually place holders for all spaces will be filled. */
      if( space_holders[ r ] ) {
        space_holders[ r ] = FALSE;
        break;
      }
    }
    while( TRUE );
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
  *result = s[ l ];
}

