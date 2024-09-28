%code requires {
#include <stdio.h>
#include "ast.h"
#include "misc.h"
typedef void* yyscan_t;
}
%code provides {
yytoken_kind_t yylex (YYSTYPE * yylval_param, yyscan_t yyscanner);
void yyerror (yyscan_t scanner, char const *s);
}

%token TK_SPACE "' '"
%token <ident> TK_ID
%token <digits> TK_DIG
%token TK_DOT "."
%token TK_HYPHEN "-"
%token TK_HYPHEN_SEP " - "
%token TK_PLUS "+"
%token TK_TILDE "~" 
%token TK_CARET "^"
%token TK_STAR "*"
%token TK_LT "<"
%token TK_GT ">"
%token TK_GE ">="
%token TK_LE "<="
%token TK_EQ "="
%token TK_OR "||"
%token TK_X "x"

%nterm <partial> partial
%nterm <nr> nr
%nterm <tilde> tilde
%nterm <caret> caret
%nterm <qualifier> qualifier
%nterm <pre> pre
%nterm <build> build
%nterm <parts> parts
%nterm <part> part

%define api.pure full
%define api.value.type {union YYSTYPE}
/* %define api.location.type {struct YYLTYPE} */
%define parse.error detailed
%param {yyscan_t scanner}
%header
/* %initial-action {
    yylloc.first_line = 0;
    yylloc.first_column = 0;
    yylloc.last_line = 0;
    yylloc.last_column = 0;
} */

%%

part: TK_ID {
        $$ = partId($1, yyget_leng(scanner));
        yyset_extra($$, scanner);
    };

%%

void yyerror (yyscan_t scanner, char const *s) {
  fprintf(stderr, "%s\n", s);
  fprintf(stderr, "while parsing: %s\n", yyget_text(scanner));
}

