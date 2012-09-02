%{
#include "lib/utility/log.tpp"

#include "modules/compiler/engine.hpp"
#include "modules/compiler/detail/parser.hpp"

#include <iostream>

#define YY_INPUT(buf, result, max_size) \
{ \
	if(yyextra->input.eof()) { \
		result = YY_NULL; \
	} else { \
		yyextra->input.read(buf, max_size); \
		result = yyextra->input.gcount(); \
	} \
}

%}

%option stack
%option debug
%option noyywrap

%option reentrant
%option extra-type="compiler::tengine*"
%option bison-bridge

%%

","						return COMMA;
";"						return END;

"("						return LEFT_PAREN;
")"						return RIGHT_PAREN;

"{"						return LEFT_BRACE;
"}"						return RIGHT_BRACE;

"::"					return SCOPE_SEPARATOR;


 /***** ***** ***** ***** Pragma section ***** ***** ****** *****/

"pragma"				return PRAGMA;
"enable"				return ENABLE;


 /***** ***** ***** ***** Import section ***** ***** ****** *****/

"import"				return IMPORT;
"buildin"				return BUILDIN;
"library"				return LIBRARY;
"program"				return PROGRAM;


 /***** ***** ***** ***** Interface section ***** ***** ****** *****/

"interface"				return INTERFACE;


 /***** ***** ***** ***** Implementation section ***** ***** ****** *****/

"implementation"		return IMPLEMENTATION;


"="						return ASSIGN;

"namespace"				return NAMESPACE;
"method"				return METHOD;

"int"					return INT;

"+"						return ADD;
"-"						return MINUS;
"*"						return MULTIPLY;

[0-9]+ {
		int result = 0;
		for(int i = 0; i < yyleng; ++i) {
			result *= 10;
			result += yytext[i] - '0';
		}
		yylval->rvalue_integer = yyextra->create_rvalue_integer(result);

		LOG_D
				<< "Matched »"
				<< std::string(yytext, yyleng)
				<< "« type »integer« value »"
				<< yylval->rvalue_integer->value()
				<< "«.\n";

		return RVALUE_INTEGER;
	}

\"([^"\\]|\.)*\" {

		const std::string string(yytext, yyleng);
		yylval->string_value = yyextra->create_rvalue_string(string);

		LOG_D
				<< "Matched »"
				<< string
				<< "« type »string«.\n";

		return RVALUE_STRING;
	}

[a-zA-Z_][a-zA-Z0-9_]*	{

		const std::string string(yytext, yyleng);
		yylval->identifier = yyextra->create_identifier(string);

		LOG_D << "Matched »" << string << "« type »identifier«.\n";

		return IDENTIFIER;
	}

"//".*					/* DO NOTHING */;
[ \t\r\n]				/* DO NOTHING */;
.						std::cerr << "parse error.\n"; yyterminate();

%%

void compiler::tengine::init_scanner()
{
	LOG_T;

	yylex_init(&scanner);
	yyset_extra(this, scanner);
}

void compiler::tengine::destroy_scanner()
{
	LOG_T;

	yylex_destroy(scanner);
}

void compiler::tengine::set_flex_debug(const bool state)
{
	yyset_debug(state, scanner);
}
