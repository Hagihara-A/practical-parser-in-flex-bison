%top {
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"
#include "parser.tab.h"

}

%option reentrant header-file="lex.yy.h" noyywrap yylineno
%option bison-bridge bison-locations
%option extra-type="RangeSet *"

%s ID

%%

<ID>[\-.[:alnum:]]+ {
    yy_update_location(yylloc, yyleng);
    BEGIN(INITIAL);
    yylval->ident = strndup(yytext, yyleng);
    return TK_ID;
}
<INITIAL>[1-9][0-9]*|0 {
    yy_update_location(yylloc, yyleng);
    yylval->digits = atoi(yytext);
    return TK_DIG;
}
<INITIAL>"." {
    yy_update_location(yylloc, yyleng);
    return TK_DOT;}
<INITIAL>"-" {
    yy_update_location(yylloc, yyleng);
    BEGIN(ID);
    return TK_HYPHEN;}
<INITIAL>"+" {
    yy_update_location(yylloc, yyleng);
    BEGIN(ID);
    return TK_PLUS;}
<INITIAL>" - " {
    yy_update_location(yylloc, yyleng);
    return TK_HYPHEN_SEP;}
<INITIAL>"~" {
    yy_update_location(yylloc, yyleng);
    return TK_TILDE;}
<INITIAL>"^" {
    yy_update_location(yylloc, yyleng);
    return TK_CARET;}
<INITIAL>"*" {
    yy_update_location(yylloc, yyleng);
    return TK_STAR;}
<INITIAL>"<" {
    yy_update_location(yylloc, yyleng);
    return TK_LT;}
<INITIAL>">" {
    return TK_GT;}
<INITIAL>">=" {
    yy_update_location(yylloc, yyleng);
    return TK_GE;}
<INITIAL>"<=" {
    yy_update_location(yylloc, yyleng);
    return TK_LE;}
<INITIAL>"=" {
    yy_update_location(yylloc, yyleng);
    return TK_EQ;}
<INITIAL>"||" {
    yy_update_location(yylloc, yyleng);
    return TK_OR;}
<INITIAL>X|x {
    yy_update_location(yylloc, yyleng);
    return TK_X;}
<INITIAL>" "+ {
    yy_update_location(yylloc, yyleng);
    return TK_SPACE;}
<<EOF>> {
    yy_update_location(yylloc, yyleng);
    return YYEOF;}

%%
