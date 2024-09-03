#ifndef ASDASDASDASDSDADFGASDG
#define ASDASDASDASDSDADFGASDG

union YYSTYPE {
  int digits;
  char *ident;
};

struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};

void print_token(const int tok, const union YYSTYPE *yysval);
#endif