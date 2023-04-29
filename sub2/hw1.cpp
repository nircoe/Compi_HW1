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
  string s = "";
  for(int i = 0; i < str.length(); i++)
  {
    if(str[i] != '\\') s += str[i];
    else 
    {
      switch (str[i + 1])
      {
        case '\\':
          s += '\\';
          i++;
          break;
        case '\"':
          s += '\"';
          i++;
          break;
        case 'x':
          if(str.substr(i + 2, 2) == "00") return s;
          s += (char)(strtol((str.substr(i + 2, 2)).c_str(), nullptr, 16));
          i += 3;
          break;
        case 'n':
          s += "\n";
          i++;
          break;
        case 'r':
          s += "\r";
          i++;
          break;
        case 't':
          s += "\t";
          i++;
          break;
        case '0':
          return s;
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
          str = "//";
          break; 
        case STRING:
            str = GetCurrectString(str);
          break;
        case UNCLOSED_STRING:
          std::cout << "Error unclosed string\n";
          exit(0);
        case SINGLE_ESCAPE_SEQUENCE:
          token = (int)STRING;
          if (str == "\"\\r\""){
              //std::cout <<"inside"<<std::endl;
              str = "\r";
          }
          if (str == "\"\\n\"")
              str = "\n";
              //std::cout<< "fucking shit";
          break;
        case HEX_ERROR:
          if(str.length() > 1) 
          {
            str = str.substr(0, 2);
            if(str[1] == '"' || str[1] == '\"' || str[1] == '\0') str = str.substr(0, 1);
          }
          else if(str.length() == 1 && str[0] == '\"') str = "";
          std::cout << "Error undefined escape sequence x" << str << "\n";
          exit(0);
        case UNDEFINED_ESCAPE_SEQUENCE:
          std::cout << "Error undefined escape sequence " << str[0] << "\n";
          exit(0);
        case INVALID_INPUT:
          std::cout << "Error " << str << "\n";
          exit(0);
    }
		std::cout << line << " " << tokennames[token-1] << " " << str << "\n";

	}
	return 0;
}
