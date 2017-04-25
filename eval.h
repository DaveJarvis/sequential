#ifndef __WMS_EVAL_H__
#define __WMS_EVAL_H__

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 32

/**
 * Pop a value off the stack.
 */
double stack_pop();

/**
 * Push a value onto the stack.
 *
 * @param element The value to push onto the stack.
 */
void stack_push( double element );

/**
 * Evalulate a Postfix Expression.
 *
 * @param expr The expression to evaluate.
 */
double evaluate_expression( const char *expr );

#endif

