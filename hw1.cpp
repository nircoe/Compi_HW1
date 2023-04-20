#include <iostream>
#include "tokens.hpp"
#define UNCLOSED_STRING           31
#define SINGLE_ESCAPE_SEQUENCE    32
#define HEX_ERROR                 33
#define UNDEFINED_ESCAPE_SEQUENCE 34
#define INVALID_INPUT             35


using std::string;

const string tokennames[] = {
	"VOID",
	"INT",
  "BYTE",
  "B",
  "BOOL",
  "AND",
  "OR",
  "NOT",
  "TRUE",
  "FALSE",
  "RETURN",
  "IF",
  "ELSE",
  "WHILE",
  "BREAK",
  "CONTINUE", 
  "SC",
  "COMMA",
  "LPAREN",
  "RPAREN",
  "LBRACE",
  "RBRACE",
  "ASSIGN",
  "RELOP",
  "BINOP",
  "COMMENT",
  "ID",
  "NUM",
  "STRING",
	"OVERRIDE"
};

string GetCurrectString(string str) 
{
  string s;
  for(int i = 0; i < str.length(); i++)
  {
    if(str[i] != '\\') s += str[i];
    else 
    {
      switch (str[i + 1])
      {
        case '\\':
          if(str[i + 2] == '\\') s += '\\';
          else                   s += '\"';
          i += 2;
          break;
        case 'x':
          s += (char)(strtol((str.substr(i + 2, 2)).c_str(), nullptr, 16));
          i + 3;
          break;
        case 'n':
          s += '\n';
          i++;
          break;
        case 'r':
          s += '\r';
          i++;
          break;
        case 't':
          s += '\t';
          i++;
          break;
        case '0':
          s += '\0';
          i++;
          break;
      }
    }
  }

  return s.substr(0, s.length() - 1);
}

int main()
{
	int token;
	while ((token = yylex())) {
	  // Your code here
		string str = yytext;
    int line = yylineno;

    switch (token)
    {
        case COMMENT:
          line--;
          str = "//";
          break; 
        case STRING:
          str = GetCurrectString(str);
          break;
        case UNCLOSED_STRING:
          std::cout << "Error unclosed string\n";
          exit(0);
        case SINGLE_ESCAPE_SEQUENCE:
          exit(0);
          // check what to print
          break;
        case HEX_ERROR:
          std::cout << "Error undefined escape sequence x" << str << "\n";
          exit(0);
        case UNDEFINED_ESCAPE_SEQUENCE:
          std::cout << "Error undefined escape sequence " << str[0] << "\n";
          exit(0);
        case INVALID_INPUT:
          std::cout << "Error " << str << "\n";
          exit(0);
    }
    //printf("%d %s %s\n", line, tokennames[token - 1].c_str(), str.c_str());
		std::cout << line << " " << tokennames[token-1] << " " << str << "\n";
    //std::cout << str << "\n";

	}
	return 0;
}
