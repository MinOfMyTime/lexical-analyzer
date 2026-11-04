%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerforflex.h"
TOKEN token;
%}



%%
program         token.type = kw_program; return kw_program;
var	        token.type = kw_var; return kw_var;
constant        token.type = kw_constant; return kw_constant;
integer         token.type = kw_integer; return kw_integer;
bool            token.type = kw_boolean; return kw_boolean;
string          token.type = kw_string; return kw_string;
float           token.type = kw_float; return kw_float;
true    	token.type = kw_true; return kw_true;
false           token.type = kw_false; return kw_false;
if              token.type = kw_if; return kw_if;
fi              token.type = kw_fi; return kw_fi;
then            token.type = kw_then; return kw_then;
else            token.type = kw_else; return kw_else;
while          	token.type = kw_while; return kw_while;
do              token.type = kw_do; return kw_do;
od              token.type = kw_od; return kw_od;
and	        token.type = kw_and; return kw_and;
or              token.type = kw_or; return kw_or;
read            token.type = kw_read; return kw_read;
write           token.type = kw_write; return kw_write;
for     	token.type = kw_for; return kw_for;
from            token.type = kw_from; return kw_from;
to              token.type = kw_to; return kw_to;
by              token.type = kw_by; return kw_by;
[a-zA-Z_][a-zA-Z0-9_]*  token.str_ptr = strdup(yytext); token.type = lx_identifier; return lx_identifier;
[+-]?[0-9]+\.[0-9]+     token.float_value = atof(yytext); token.type = lx_float; return lx_float;
[+-]?[0-9]+             token.value = atoi(yytext); token.type = lx_integer; return lx_integer;
\"[^"\n]*\"             token.str_ptr = strdup(yytext); token.type = lx_string; return lx_string;
"("     {token.type = lx_Iparen; return lx_Iparen;}
")"     {token.type = lx_rparen; return lx_rparen;}
"["     {token.type = lx_lbracket; return lx_lbracket;}
"]"     {token.type = lx_rbracket; return lx_rbracket;}
":"	{token.type = Ix_colon; return Ix_colon;}
"."     {token.type = lx_dot; return lx_dot;}
";"     {token.type = lx_semicolon; return lx_semicolon;}
","     {token.type = lx_comma; return lx_comma;}
":="    {token.type = Ix_colon_eq; return Ix_colon_eq;}
"+"     {token.type = lx_plus; return lx_plus;}
"-"     {token.type = lx_minus; return lx_minus;}
"*"     {token.type = lx_star; return lx_star;}
"/"     {token.type = lx_slash; return lx_slash;}
"="	{token.type = lx_eq; return lx_eq;}
"!="    {token.type = lx_neq; return lx_neq;}
"<="    {token.type = lx_le; return lx_le;}
"<"     {token.type = lx_lt; return lx_lt;}
">="    {token.type = lx_ge; return lx_ge;}
">"     {token.type = lx_gt; return lx_gt;}
##[^#]*##         /*Consume short comments*/
#.*\n          /*Consume long comments*/
[ \t\n]+         /* ignore whitespace */;
.              token.type = lx_error; return lx_error;
%%


int yywrap(void)
{
    return 1;
}
int main( int argc, char **argv )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    return yylex();
    }