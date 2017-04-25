#include "eval.h"

double STACK[ STACK_SIZE ];
int stack_top = -1;

/**
 * Pops an operand off the stack.
 */
double stack_pop() {
  return STACK[ stack_top-- ];
}
 
/**
 * Pushes an operand onto the stack.
 */
void stack_push( double element ) {
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
  /* Expression will never exceed 64 characters. */
  char eval[ 64 ];

  strcpy( eval, expr );
  
  char *token = strtok( eval, " " );

  while( token != NULL ) {
    char ch = *token;

    if( isdigit( ch ) ) {
      stack_push( atoi( token ) );
    }
    else {
      double operand2 = stack_pop();
      double operand1 = stack_pop();

      switch( ch ) {
        case '+': stack_push( operand1 + operand2 ); break;
        case '-': stack_push( operand1 - operand2 ); break;
        case '*': stack_push( operand1 * operand2 ); break;
        case '/': stack_push( operand1 / operand2 ); break;
        case '^': stack_push( pow( operand1, operand2 ) ); break;
      }
    }

    token = strtok( NULL, " " );
  }

  return stack_pop();
}

