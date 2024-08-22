%code requires {
#include <stdio.h>
#include "parser.h"
typedef void* yyscan_t;
}
%code provides {
int yylex (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
void yyerror (YYLTYPE *yylloc, yyscan_t scanner, char const *s);
}

%token TK_SPACE " "
%token <ident> TK_ID
%token <digits> TK_DIG
%token TK_DOT "."
%token TK_HYPHEN "-"
%token TK_HYPHEN_SEP " - "
%token TK_PLUS "+"
%token TK_TILDE "~" 
%token TK_CARET "^"
%token TK_LT "<"
%token TK_GT ">"
%token TK_GE ">="
%token TK_LE "<="
%token TK_EQ "="
%token TK_OR "||"
%token TK_X "X"
%type <digits> range_set

%define api.pure full
%define api.value.type {union YYSTYPE}
%define api.location.type {struct YYLTYPE}
%param {yyscan_t scanner}
%header


%%
range_set:
    TK_DIG {
        @$ = @1;
}
%%

void yyerror (YYLTYPE *yylloc, yyscan_t scanner, char const *s) {
  fprintf (stderr, "%s\n", s);
}

