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
%token <ident> TK_ID "identifier"
%token <digits> TK_DIG "digits"
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
%nterm <range_set> range_set
%nterm <range> range
%nterm <simples> simples
%nterm <hyphen> hyphen
%nterm <simple> simple
%nterm <primitive> primitive
%nterm <compare> compare
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

%start range_set

%%

range_set
    : range {
        $$ = range_set_singleton($1);
        yyset_extra($$, scanner); }
    | range_set "||" range { 
        $$ = range_set_append($1, $3);
        yyset_extra($$, scanner); }
    ;

range
    : hyphen { $$ = range_hyphen($1); }
    | simples { $$ = range_simples($1); }
    | /* empty */ { $$ = range_void(); }
    ;

simples
    : simple { $$ = simples_singleton($1); }
    | simples "' '" simple { $$ = simples_append($1, $3); }
    ;
hyphen
    : partial " - " partial { $$ = hyphen($1, $3); }
    ;
simple
    : primitive { $$ = simple_primitive($1); }
    | partial { $$ = simple_partial($1); }
    | tilde { $$ = simple_tilde($1); }
    | caret { $$ = simple_caret($1); }
    ;
primitive
    : compare partial { $$ = primitive($1, $2); }
    ;
compare
    : "<" { $$ = CompLt; }
    | ">" { $$ = CompGt; }
    | ">=" { $$ = CompGte; }
    | "<=" { $$ = CompLte; }
    | "="   { $$ = CompEq; }
    ;

partial
    : x { $$ = partial0(); }
    | x "." xr { $$ = partial0(); }
    | x "." xr "." xr { $$ = partial0(); }
    | nr { $$ = partial1($1); }
    | nr "." x { $$ = partial1($1); }
    | nr "." x "." xr { $$ = partial1($1); }
    | nr "." nr { $$ = partial2($1, $3); }
    | nr "." nr "." x { $$ = partial2($1, $3); }
    | nr "." nr "." nr qualifier { $$ = partial3($1, $3, $5, $6); }
    ;

xr
    : x {}
    | nr {}
    ;

x
    : "x" {}
    | "*" {}
    ;

nr
    :"digits" { $$ = $1; }
    ;

tilde
    : "~" partial { $$ = $2; }
    | "~" "' '" partial { $$ = $3; }
    ;

caret
    : "^" partial { $$ = $2; }
    | "^" "' '" partial { $$ = $3; }
    ;

qualifier: 
    /* empty */ { $$ = qualifier(NULL, NULL); }
    | "-" pre  { $$ = qualifier($2, NULL); }
    | "+" build { $$ = qualifier(NULL, $2); }
    | "-" pre "+" build { $$ = qualifier($2, $4); }
    ;

pre:
    parts { $$ = parts_singleton($1); }
    ;

build:
    parts { $$ = parts_singleton($1); }
    ;

parts:
    parts "." part {  $$ = parts_append($1, $3); }
    | part { $$ = parts_singleton($1); }
    ;


part:
    nr { 
        $$ = partNr($1);
        print_part($$, 0);
        
         }
    | "identifier" { $$ = partId($1, yyget_leng(scanner));
        print_part($$, 0);
        
     }
    ;

%%

void yyerror (yyscan_t scanner, char const *s) {
  fprintf(stderr, "%s\n", s);
}

