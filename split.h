#ifndef __WMS_SPLIT_H__
#define __WMS_SPLIT_H__

#include <string.h>

#include "random.h"

/**
 * Split a set of characters into randomly-sized parts.
 *
 * @param s The set of characters to split.
 * @param buffer The memory location for the split results.
 * @param n The number of subsets to create.
 */
void split( const char *s, char *result, int n );

#endif

