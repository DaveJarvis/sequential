#include "eval.h"

double STACK[ STACK_SIZE ];
int stack_top = -1;

double stack_pop() {
  return STACK[ stack_top-- ];
}
 
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
  double operand1, operand2;

  char *eval = strdup( expr );
  char *token = strtok( eval, " " );

  while( token != NULL ) {
    char ch = *token;

    if( isdigit( ch ) ) {
      stack_push( atoi( token ) );
    }
    else {
      operand2 = stack_pop();
      operand1 = stack_pop();

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

  free( eval );

  return stack_pop();
}

