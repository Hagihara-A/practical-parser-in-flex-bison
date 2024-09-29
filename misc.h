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

void print_token(const int tok, const union YYSTYPE *yysval,
                 const struct YYLTYPE *yylloc);
void yy_update_location(struct YYLTYPE *yylloc, size_t leng);

#endif