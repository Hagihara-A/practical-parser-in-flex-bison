%top {
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"
#include "parser.tab.h"
}

%option bison-bridge reentrant header-file="lex.yy.h" noyywrap yylineno
%option extra-type="RangeSet *"

%s ID

%%

<ID>[\-.[:alnum:]]+ {
    BEGIN(INITIAL);
    yylval->ident = strndup(yytext, yyleng);
    return TK_ID;
}
<INITIAL>[1-9][0-9]*|0 {
    yylval->digits = atoi(yytext);
    return TK_DIG;
}
<INITIAL>"." {return TK_DOT;}
<INITIAL>"-" {BEGIN(ID);
    return TK_HYPHEN;}
<INITIAL>"+" {BEGIN(ID);
    return TK_PLUS;}
<INITIAL>" - " {return TK_HYPHEN_SEP;}
<INITIAL>"~" {return TK_TILDE;}
<INITIAL>"^" {return TK_CARET;}
<INITIAL>"*" {return TK_STAR;}
<INITIAL>"<" {return TK_LT;}
<INITIAL>">" {return TK_GT;}
<INITIAL>">=" {return TK_GE;}
<INITIAL>"<=" {return TK_LE;}
<INITIAL>"=" {return TK_EQ;}
<INITIAL>"||" {return TK_OR;}
<INITIAL>X|x {return TK_X;}
<INITIAL>" "+ {return TK_SPACE;}
<<EOF>> {return YYEOF;}

%%
