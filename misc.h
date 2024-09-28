#ifndef ASDASDASDASDSDADFGASDG
#define ASDASDASDASDSDADFGASDG

#include "ast.h"

union YYSTYPE {
  int digits;
  char *ident;
  RangeSet *range_set;
  Range *range;
  Simples *simples;
  Hyphen *hyphen;
  Simple *simple;
  Primitive *primitive;
  Compare compare;
  Partial *partial;
  Tilde *tilde;
  Caret *caret;
  Qualifier *qualifier;
  Build *build;
  Pre *pre;
  Parts *parts;
  Part *part;
  Nr nr;
};

struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};

void print_token(const int tok, const union YYSTYPE *yysval);
#endif