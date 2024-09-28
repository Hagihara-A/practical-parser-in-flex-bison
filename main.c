#include <stdio.h>

#include "ast.h"
#include "lex.yy.h"
#include "misc.h"
#include "parser.tab.h"

int main(void) {
  Part* part = NULL;
  yyscan_t scanner;
  yylex_init_extra(part, &scanner);
  int parse_result = yyparse(scanner);
  Part* ast = yyget_extra(scanner);
  print_part(ast);
  yylex_destroy(scanner);
  if (parse_result == 0) {
    printf("parse success\n");
  } else {
    printf("parse failed\n");
  }
  return 0;
}