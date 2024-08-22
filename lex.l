%top {
#include <stdio.h>
#include "parser.h"
#include "parser.tab.h"
}

%option bison-bridge bison-locations reentrant header-file="lex.yy.h" noyywrap

%%

[:space:]+ {return TK_SPACE;}
[\-\+]^[:alnum:] {
    yylval->ident = strdup(yytext);
    
    return TK_ID;}
"0" {return TK_ID;}
[1-9][0-9] {return TK_ID;}
"." {return TK_DOT;}
"-" {return TK_HYPHEN;}
[:space:]*" - "[:space:]* {return TK_HYPHEN_SEP;}
"+" {return TK_PLUS;}
"*" {return TK_TILDE;}
"<" {return TK_LT;}
">" {return TK_GT;}
">=" {return TK_GE;}
"<=" {return TK_LE;}
"=" {return TK_EQ;}
[:space:]*"||"[:space:]* {return TK_OR;}
X|x {return TK_X;}

%%
