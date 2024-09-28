#include <stdio.h>

#include "ast.h"
#include "lex.yy.h"
#include "misc.h"
#include "parser.tab.h"

int main(void) {
    // yyscan_t sc2;
    // yylex_init_extra(NULL, &sc2);
    // yytoken_kind_t token;
    // YYSTYPE yylval;
    // do {
    //   token = yylex(&yylval, sc2);
    //   print_token(token, &yylval);
    // } while (token != YYEOF);

  yyscan_t scanner;
  yylex_init_extra(NULL, &scanner);
  int parse_result = yyparse(scanner);
  RangeSet* ast = yyget_extra(scanner);
  print_range_set(ast, 0);
  yylex_destroy(scanner);
  if (parse_result == 0) {
    printf("parse success\n");
  } else {
    printf("parse failed\n");
  }
  return parse_result;
}