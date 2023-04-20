%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap

void "void"
int "int"
byte "byte"
b "b"
bool "bool"
override "override"
and "and"
or "or"
not "not"
true "true"
false "false"
return "return"
if "if"
else "else"
while "while"
break "break"
continue "continue"
sc (\;)
comma (\,)
lparen (\()
rparen(\))
lbrace (\{)
rbrace (\})
assign (\=)
relop (==|!=|<|>|<=|>=)
binop ([\+\-\*\/])
comment (\/\/[^\n\r]*[\r\n(\r\n)(\n\r)]?)
id ([a-zA-z][a-zA-Z0-9]*)
num (([1-9]+[0-9]*)|0)
digit ([0-9])
letter ([a-zA-Z])
whitespace ([ \t\n\r])

printable_char ([^\r\n\"\\])
legal_hex (\\x[0-7][0-9a-fA-F])
illegal_hex (([^0-7][^0-9a-fA-F])|([^0-7][0-9a-fA-F])|([0-7][^0-9a-fA-F]))
escape_sequence (\\[\\\"nrt0])
illegal_escape_sequence ([^\\\"nrt0x])

string (({printable_char}|{escape_sequence}|{legal_hex})*\")
unclosed_string (({printable_char}|{escape_sequence}|{legal_hex})*[\n\r<<EOF>>]*)
begin_escape_sequence (({printable_char}|{escape_sequence}|{legal_hex})*\\)

%x STR
%x ESC_SEQ
%x STR_HEX

%%

{void}                      return VOID;
{int}                       return INT;
{byte}                      return BYTE;
{b}                         return B;
{bool}                      return BOOL;
{override}                  return OVERRIDE;
{and}                       return AND;
{or}                        return OR;
{not}                       return NOT;
{true}                      return TRUE;
{false}                     return FALSE;
{return}                    return RETURN;
{if}                        return IF;
{else}                      return ELSE;
{while}                     return WHILE;
{break}                     return BREAK;
{continue}                  return CONTINUE;
{sc}                        return SC;
{comma}                     return COMMA;
{lparen}                    return LPAREN;
{rparen}                    return RPAREN;
{lbrace}                    return LBRACE;
{rbrace}                    return RBRACE;
{assign}                    return ASSIGN;
{relop}                     return RELOP;
{binop}                     return BINOP;
{comment}                   return COMMENT;
{id}                        return ID;
{num}                       return NUM;
{whitespace}				;

(\"(\\[nr])+\")             return 32;  
(\")                        BEGIN(STR);
<STR>{string}               { BEGIN(INITIAL); return STRING; }
<STR>{unclosed_string}      { BEGIN(INITIAL); return 31; }
<STR>{begin_escape_sequence} BEGIN(ESC_SEQ);           
<ESC_SEQ>(x)                BEGIN(STR_HEX);
<ESC_SEQ>{illegal_escape_sequence}   { BEGIN(INITIAL); return 34; }
<STR_HEX>{illegal_hex}      { BEGIN(INITIAL); return 33; }

.		                    return 35;

%%

