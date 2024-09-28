%top {
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"
#include "parser.tab.h"
}

%option bison-bridge reentrant header-file="lex.yy.h" noyywrap yylineno
%option extra-type="Part *"

%%

[\-+][\-.[:alnum:]]+ {
    int ident_len = yyleng * sizeof(char); 
    char *id_start = yytext + sizeof(char);
    yylval->ident = strndup(id_start, yyleng);
    return TK_ID;
}
[1-9][0-9]*|0 {
    yylval->digits = atoi(yytext);
    return TK_DIG;
}
"." {return TK_DOT;}
"-" {return TK_HYPHEN;}
" - " {return TK_HYPHEN_SEP;}
"+" {return TK_PLUS;}
"~" {return TK_TILDE;}
"^" {return TK_CARET;}
"*" {return TK_STAR;}
"<" {return TK_LT;}
">" {return TK_GT;}
">=" {return TK_GE;}
"<=" {return TK_LE;}
"=" {return TK_EQ;}
"||" {return TK_OR;}
X|x {return TK_X;}
" "+ {return TK_SPACE;}
<<EOF>> {return YYEOF;}
.+ {return YYUNDEF;}

%%
