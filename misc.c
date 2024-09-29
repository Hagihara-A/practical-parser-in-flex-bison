#include "misc.h"

#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

void print_token(const int tok, const union YYSTYPE *yysval,
                 const struct YYLTYPE *yylloc) {
  switch (tok) {
    case TK_SPACE:
      printf("' '");
      break;
    case TK_ID:
      printf("%s (identifier)", yysval->ident);
      break;
    case TK_DIG:
      printf("%d (digit)", yysval->digits);
      break;
    case TK_DOT:
      printf("'.'");
      break;
    case TK_HYPHEN:
      printf("'-'");
      break;
    case TK_HYPHEN_SEP:
      printf("' - '");
      break;
    case TK_PLUS:
      printf("'+'");
      break;
    case TK_TILDE:
      printf("'~'");
      break;
    case TK_CARET:
      printf("'^'");
      break;
    case TK_LT:
      printf("'<'");
      break;
    case TK_GT:
      printf("'>'");
      break;
    case TK_GE:
      printf("'>='");
      break;
    case TK_LE:
      printf("'<='");
      break;
    case TK_EQ:
      printf("'='");
      break;
    case TK_OR:
      printf("'||'");
      break;
    case TK_X:
      printf("'X'");
      break;
    case YYEOF:
      printf("<<EOF>>");
      break;
    default:
      printf("token: %d", tok);
      break;
  }
  printf(" at %d:%d-%d:%d\n", yylloc->first_line, yylloc->first_column,
         yylloc->last_line, yylloc->last_column);
}

void yy_update_location(struct YYLTYPE *yylloc, size_t leng) {
  yylloc->first_column = yylloc->last_column;
  yylloc->last_column = yylloc->last_column + leng;
}