#include <stdio.h>

#include "lex.yy.h"
#include "misc.h"
#include "parser.tab.h"

int main(void) {
  yyscan_t scanner;
  yylex_init(&scanner);
  int parse_result = yyparse(scanner);
  YYSTYPE* yylval = yyget_lval(scanner);
  print_part(yylval);
  yylex_destroy(scanner);
  if (parse_result == 0) {
    printf("parse success\n");
  } else {
    printf("parse failed\n");
  }
  return 0;
}