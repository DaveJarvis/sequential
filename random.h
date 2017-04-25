#ifndef __WMS_RANDOM_H__
#define __WMS_RANDOM_H__

#define _GNU_SOURCE

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/random.h>
#include <sys/syscall.h>

#define getrandom(dst,s,flags) syscall(SYS_getrandom, (void*)dst, (size_t)s, (unsigned int)flags)

/* Entropy buffer size. */
#define MAX_ENTROPY_SIZE 255

#define FALSE 0
#define TRUE (!FALSE)

/**
 * Compute a uniform random number.
 */
unsigned char rnd();

#endif

