%pure-parser
%parse-param { tengine* engine }
%lex-param { void* scanner  }

%{
	#define YYDEBUG 1

	#include "lib/utility/concatenate.tpp"
	#include "lib/utility/log.tpp"
	#include "modules/compiler/engine.hpp"
	#include "modules/compiler/detail/node.hpp"
	#include "modules/compiler/exception.hpp"
%}
 /**
  * @todo seems the union can be split in several unions.
  * Also seems destructors are possible.
  * Bison 2.5 PDF page 69.
  */
%union {
	/* tokens */
	compiler::detail::node::tidentifier* identifier;
	compiler::detail::node::trvalue_integer* rvalue_integer;
	compiler::detail::node::trvalue_string* string_value;

	/* types */
	compiler::detail::node::tnode_* node;
	compiler::detail::node::tvalue_* value;

	compiler::detail::node::tqualified_identifier* qualified_identifier;

	compiler::detail::node::tprogram* program;
	compiler::detail::node::targument_list* argument_list;
	compiler::detail::node::tstatement_list* statement_list;

}

%{
	using compiler::tengine;

	int yylex(YYSTYPE* lvalp, void* scanner);

	void yy_compiler_error(tengine* /*engine*/, const char* s)
	{
		LOG_F << s;
	}

	#define scanner engine->scanner
%}

%token COMMA END

%token LEFT_PAREN RIGHT_PAREN
%token LEFT_BRACE RIGHT_BRACE

%token SCOPE_SEPARATOR

%token PRAGMA ENABLE
%token IMPORT BUILDIN LIBRARY PROGRAM

%token INTERFACE
%token IMPLEMENTATION

%token ASSIGN

%token NAMESPACE
%token METHOD

%token INT

%token ADD MINUS MULTIPLY

%token<rvalue_integer> RVALUE_INTEGER
%token<rvalue_string> RVALUE_STRING

%token<identifier> IDENTIFIER

/***********/

%type<program> program

%type<node> section_interface
%type<statement_list> declaration_list
%type<node> declaration

%type<node> section_implementation
%type<statement_list> definition_list
%type<node> definition

%type<node> declaration_method
%type<argument_list> declaration_procedure_argument_block
%type<argument_list> declaration_procedure_argument_list
%type<identifier> declaration_procedure_argument

%type<node> declaration_namespace
%type<node> definition_namespace
%type<node> definition_method
%type<argument_list> definition_procedure_argument_block
%type<argument_list> definition_procedure_argument_list
%type<identifier> definition_procedure_argument
%type<node> statement_block
%type<statement_list> statement_list
%type<node> statement
%type<node> integer_definition

%type<qualified_identifier> qualified_identifier
%type<qualified_identifier> scoped_identifier

%type<value> rvalue factor term expression

%left ADD MINUS
%left MULTIPLY

%start program

%%

program
		: section_pragma
		  section_import
		  section_interface
		  section_implementation
			{
				$$ = engine->create_program($3, $4);
			}
		| section_import section_interface section_implementation
			{
				$$ = engine->create_program($2, $3);
			}
		;

/***** ***** ***** ***** Pragma section ***** ***** ****** *****/

section_pragma
		: PRAGMA END
		| PRAGMA END pragma_list
		;

pragma_list
		: pragma
		| pragma_list pragma
		;

pragma
		: ENABLE IDENTIFIER END
			{
				if($2->name() == "debug_lexer") {
					engine->set_flex_debug(true);
				} else if($2->name() == "debug_parser") {
					yydebug = 1;
				} else {
					throw compiler::exception::tundefined(lib::concatenate(
							  "Pragma »"
							, $2->name()
							, "« is unknown."));
				}
			}
		;


/***** ***** ***** ***** Import section ***** ***** ****** *****/

section_import
		: /* blank */
		| IMPORT END
		| IMPORT END import_list
		;

import_list
		: import
			{
				throw compiler::exception::tundefined(
						"Imports are not yet implemented.");
			}
		| import_list import
		;

import
		: BUILDIN RVALUE_STRING END
		| LIBRARY RVALUE_STRING END
		| PROGRAM RVALUE_STRING END
		;


/***** ***** ***** ***** Interface section ***** ***** ****** *****/

section_interface
		: INTERFACE END declaration_list
			{
				$$ = $3;
			}
		;

declaration_list
		: declaration
			{
				$$ = engine->create_statement_list();
				$$->add($1);
			}
		| declaration_list declaration
			{
				$1->add($2);
				$$ = $1;
			}
		;

declaration
		: declaration_variable
		| declaration_namespace
/*		| declaration_struct */
/*		| declaration_class */
		| declaration_method
/*		| declaration_function */
/*		| declaration_template */
		;

declaration_namespace
		: NAMESPACE IDENTIFIER LEFT_BRACE
			{
				engine->named_scope_enter($2);
			}
		  declaration_list RIGHT_BRACE
			{
				engine->named_scope_leave();
				$$ = &compiler::detail::nop;
			}
		;

declaration_variable
		: integer_definition
		;

declaration_method
		: METHOD IDENTIFIER declaration_procedure_argument_block END
			{
				engine->declare_method($2, $3);
				$$ = &compiler::detail::nop;
			}
		;

declaration_procedure_argument_block
		: LEFT_PAREN RIGHT_PAREN
			{
				$$ = engine->create_argument_list();
			}
		| LEFT_PAREN declaration_procedure_argument_list RIGHT_PAREN
			{
				$$ = $2;
			}
		;

declaration_procedure_argument_list
		: declaration_procedure_argument
			{
				$$ = engine->create_argument_list();
				$$->add($1);
			}
		| declaration_procedure_argument_list
		  COMMA
		  declaration_procedure_argument
			{
				$1->add($3);
				$$ = $1;
			}
		;

declaration_procedure_argument
		: INT IDENTIFIER
			{
				$$ = $2;
			}
		;

/***** ***** ***** ***** Implementation section ***** ***** ****** *****/

section_implementation
		: IMPLEMENTATION END
			{
				$$ = engine->create_statement_list();
			}
		| IMPLEMENTATION END definition_list
			{
				$$ = $3;
			}
		;

definition_list
		: definition
			{
				$$ = engine->create_statement_list();
				$$->add($1);
			}
		| definition_list definition
			{
				$1->add($2);
				$$ = $1;
			}
		;

definition
		: definition_namespace
			{
				$$ = $1;
			}
		| definition_method
			{
				$$ = $1;
			}
		| integer_definition
			{
				$$ = $1;
			}
		;

definition_namespace
		: NAMESPACE IDENTIFIER LEFT_BRACE
			{
				engine->named_scope_enter($2);
			}
		  definition_list RIGHT_BRACE
			{
				engine->named_scope_leave();
				$$ = $5;
			}
		;

definition_method
		: METHOD
		  IDENTIFIER
		  definition_procedure_argument_block
		  statement_block
			{
				$$ = engine->create_definition_method($2, $3, $4);
			}
		;

definition_procedure_argument_block
		: LEFT_PAREN RIGHT_PAREN
			{
				$$ = engine->create_argument_list();
			}
		| LEFT_PAREN definition_procedure_argument_list RIGHT_PAREN
			{
				$$ = $2;
			}
		;

definition_procedure_argument_list
		: definition_procedure_argument
			{
				$$ = engine->create_argument_list();
				$$->add($1);
			}
		| definition_procedure_argument_list
		  COMMA
		  definition_procedure_argument
			{
				$1->add($3);
				$$ = $1;
			}
		;

definition_procedure_argument
		: INT IDENTIFIER
			{
				$$ = $2;
			}
		;

statement_block
		: LEFT_BRACE statement_list RIGHT_BRACE
			{
				$$ = $2;
			}
		;

statement_list
		: /* blank */
			{
				$$ = engine->create_statement_list();
			}
		| statement
			{
				$$ = engine->create_statement_list();
				$$->add($1);
			}
		| statement_list statement
			{
				$1->add($2);
				$$ = $1;
			}
		;

statement
		: IDENTIFIER ASSIGN expression END
			{
				$$ = engine->create_statement_assign($1, $3);
			}
		| qualified_identifier LEFT_PAREN RIGHT_PAREN END
			{
				$$ = engine->create_statement_procedure_call($1);
			}
		;

expression
		: term
			{
				$$ = $1;
			}
		;

term
		: term ADD factor
			{
				$$ = engine->create_expression_add($1, $3);
			}
		| term MINUS factor
			{
				$$ = engine->create_expression_subtract($1, $3);
			}
		| factor
			{
				$$ = $1;
			}
		;

factor
		: factor MULTIPLY rvalue
			{
				$$ = engine->create_expression_multiply($1, $3);
			}
		| rvalue
			{
				$$ = engine->create_expression_load($1);
			}
		;

rvalue
		: RVALUE_INTEGER
			{
				$$ = $1;
			}
		| qualified_identifier
			{
				$$ = engine->create_rvalue_variable($1);
			}
		| LEFT_PAREN expression RIGHT_PAREN
			{
				$$ = $2;
			}
		;

qualified_identifier
		: scoped_identifier
			{
				$$ = $1;
			}
		| SCOPE_SEPARATOR scoped_identifier
			{
				$2->set_fully_qualified(true);
				$$ = $2;
			}
		;

scoped_identifier
		: IDENTIFIER
			{
				$$ = engine->create_qualified_identifier($1);
			}
		| scoped_identifier SCOPE_SEPARATOR IDENTIFIER
			{
				$1->add($3);
				$$ = $1;
			}
		;

integer_definition
		: INT IDENTIFIER ASSIGN RVALUE_INTEGER END
			{
				$$ = engine->create_integer_definition($2, $4);
			}
		;

%%
