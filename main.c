#include <stdio.h>

#include "parser.tab.h"
#include "lex.yy.h"

int main(void) {
  yyscan_t scanner;
  yylex_init(&scanner);
  int retval = yyparse(scanner);
  yylex_destroy(scanner);
  return retval;
}