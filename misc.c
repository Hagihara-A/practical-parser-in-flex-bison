#include "misc.h"

#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

void print_token(const int tok, const union YYSTYPE *yysval) {
  switch (tok) {
    case TK_SPACE:
      printf("' '\n");
      break;
    case TK_ID:
      printf("%s (identifier)\n", yysval->ident);
      break;
    case TK_DIG:
      printf("%d (digit)\n", yysval->digits);
      break;
    case TK_DOT:
      printf("'.'\n");
      break;
    case TK_HYPHEN:
      printf("'-'\n");
      break;
    case TK_HYPHEN_SEP:
      printf("' - '\n");
      break;
    case TK_PLUS:
      printf("'+'\n");
      break;
    case TK_TILDE:
      printf("'~'\n");
      break;
    case TK_CARET:
      printf("'^'\n");
      break;
    case TK_LT:
      printf("'<'\n");
      break;
    case TK_GT:
      printf("'>'\n");
      break;
    case TK_GE:
      printf("'>='\n");
      break;
    case TK_LE:
      printf("'<='\n");
      break;
    case TK_EQ:
      printf("'='\n");
      break;
    case TK_OR:
      printf("'||'\n");
      break;
    case TK_X:
      printf("'X'\n");
      break;
    case YYEOF:
      printf("<<EOF>>\n");
      break;
    default:
      printf("token: %d\n", tok);
      break;
  }
}