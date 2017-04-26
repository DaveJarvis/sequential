#include "eval.h"

mpfr_ptr STACK[ STACK_SIZE ];
int stack_top = -1;

/**
 * Pops a value off the stack.
 */
mpfr_ptr stack_pop() {
  return STACK[ stack_top-- ];
}
 
/**
 * Pushes a value onto the stack.
 */
void stack_push( mpfr_ptr element ) {
  STACK[ ++stack_top ] = element;
}
 
/**
 * Evalulates a Postfix Expression, accepting +, -, *, /, and ^. Tokens
 * must be separated by spaces. This will make a copy of the expression
 * prior to parsing so as to preserve the original expression.
 *
 * @param expr The expression to evaluate.
 */
double evaluate_expression( const char *expr ) {
  /* Excessive digit set will SEGFAULT; 64 is fine for default set. */
  char eval[ 256 ];
  double result = -1;

  strcpy( eval, expr );
  
  char *token = strtok( eval, " " );

  while( token != NULL ) {
    char ch = *token;

    if( isdigit( ch ) ) {
      mpfr_ptr number = (mpfr_ptr)malloc( sizeof( mpfr_t ) );
      mpfr_init( number );

      mpfr_set_d( number, atoi( token ), GMP_RNDN );
      stack_push( number );
    }
    else {
      mpfr_ptr operand2 = stack_pop();
      mpfr_ptr operand1 = stack_pop();

      mpfr_ptr number = (mpfr_ptr)malloc( sizeof( mpfr_t ) );
      mpfr_init( number );

      switch( ch ) {
        case '+': mpfr_add( number, operand1, operand2, GMP_RNDN ); break;
        case '-': mpfr_sub( number, operand1, operand2, GMP_RNDN ); break;
        case '*': mpfr_mul( number, operand1, operand2, GMP_RNDN ); break;
        case '/': mpfr_div( number, operand1, operand2, GMP_RNDN ); break;
        case '^': mpfr_pow( number, operand1, operand2, GMP_RNDN ); break;
      }

      stack_push( number );

      mpfr_clear( operand2 );
      mpfr_clear( operand1 );
      free( operand2 );
      free( operand1 );
    }

    token = strtok( NULL, " " );
  }

  mpfr_ptr number = stack_pop();
  result = mpfr_get_d( number, GMP_RNDN );
  mpfr_clear( number );
  free( number );

  return result;
}

