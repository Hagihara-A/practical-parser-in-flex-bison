#include <stdio.h>

#include "lex.yy.h"
#include "misc.h"
#include "parser.tab.h"

int main(void) {
  yyscan_t scanner;
  yylex_init(&scanner);
  int tok;
  YYSTYPE val;
  YYLTYPE loc = {
      .first_line = 0, .first_column = 0, .last_line = 0, .last_column = 0};
  do {
    tok = yylex(&val, &loc, scanner);
    print_token(tok, &val);
  } while (tok != 0);
  yylex_destroy(scanner);
  printf("done\n");
  return 0;
}