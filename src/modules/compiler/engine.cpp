/*
 * Copyright (C) 2012 by Mark de Wever <koraq@xs4all.nl>
 * Part of the Drakken project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 *
 * See the COPYING file for more details.
 */


#include "modules/compiler/engine.hpp"

#include "lib/utility/foreach.tpp"
#include "lib/utility/log.tpp"
#include "lib/utility/validate.tpp"
#include "modules/compiler/exception.hpp"

#include <iostream>

int yy_compiler_parse(compiler::tengine*);
extern int yy_compiler_debug;

namespace compiler {

tengine::tengine(std::ostream& output, std::istream& input)
	: scanner(NULL)
	, input(input)
	, output_(output)
	, identifiers_()
	, strings_()
	, nodes_()
	, program_(NULL)
	, symbol_table_()
	, main_signature_()
{
	LOG_T;

	init_scanner();
}

tengine::~tengine()
{
	LOG_T;

	destroy_scanner();

	FOREACH(node, nodes_) {
		delete node;
	}
}

void
tengine::run()
{
	PRE_CONDITION(!program_);

	LOG_T;

	yy_compiler_debug = 0;

	int result = yy_compiler_parse(this);
	if(result) {
		throw result;
	}

	symbol_table_.validate();

	ASSERTION(program_);

	program_->generate_code(output_);
}

	/***** Lexer node. *****/


detail::node::trvalue_integer*
tengine::create_rvalue_integer(const int value)
{
	LOG_T;

	return create_node(new detail::node::trvalue_integer(value));
}

detail::node::trvalue_string*
tengine::create_rvalue_string(const std::string& value)
{
	LOG_T << "Value " << value;

	const std::set<std::string>::iterator& itor
			= strings_.insert(value).first;

	return create_node(new detail::node::trvalue_string(&*itor));
}

detail::node::tidentifier*
tengine::create_identifier(const std::string& name)
{
	LOG_T << "Name " << name;

	const std::set<std::string>::iterator& itor
			= identifiers_.insert(name).first;

	return create_node(new detail::node::tidentifier(&*itor));
}

	/***** Parser node. *****/

detail::node::tprogram*
tengine::create_program(
		  detail::node::tnode_* interface
		, detail::node::tnode_* implementation)
{
	PRE_CONDITION(interface);
	PRE_CONDITION(implementation);
	PRE_CONDITION(!program_);

	LOG_T;

	program_ = create_node(new detail::node::tprogram(
			  interface
			, implementation
			, main_signature_));

	return program_;
}

detail::node::tstatement_list*
tengine::create_statement_list()
{
	LOG_T;

	return create_node(new detail::node::tstatement_list());
}

detail::node::targument_list*
tengine::create_argument_list()
{
	LOG_T;

	return create_node(new detail::node::targument_list());
}

detail::node::tdefinition_method*
tengine::create_definition_method(
		  detail::node::tidentifier* name
		, detail::node::targument_list* argument_list
		, detail::node::tnode_* statement_list)
{
	PRE_CONDITION(name);
	PRE_CONDITION(argument_list);
	PRE_CONDITION(statement_list);

	LOG_T << "Name " << name->name();

	detail::node::tdefinition_method* result
			= create_node(new detail::node::tdefinition_method(
				  symbol_table_.current_scope()
				, name
				, argument_list
				, statement_list));

	symbol_table_.create_method(name->name(), result->get_signature(), true);

	return result;
}

detail::node::tstatement_assign*
tengine::create_statement_assign(
		  detail::node::tidentifier* lhs
		, detail::node::tnode_* rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);

	LOG_T << "Identifier " << lhs->name();

	return create_node(new detail::node::tstatement_assign(lhs, rhs));
}

detail::node::tstatement_procedure_call*
tengine::create_statement_procedure_call(
		detail::node::tqualified_identifier* procedure)
{
	PRE_CONDITION(procedure);

	LOG_T;

	const detail::symbol::tprocedure& symbol
			= symbol_table_.find_method(*procedure);

	return create_node(
			  new detail::node::tstatement_procedure_call(symbol.signature));
}

detail::node::texpression_add*
tengine::create_expression_add(
		  detail::node::tvalue_* lhs
		, detail::node::tvalue_* rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);

	LOG_T;

	return create_node(new detail::node::texpression_add(lhs, rhs));
}

detail::node::texpression_subtract*
tengine::create_expression_subtract(
		  detail::node::tvalue_* lhs
		, detail::node::tvalue_* rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);

	LOG_T;

	return create_node(new detail::node::texpression_subtract(lhs, rhs));
}

detail::node::texpression_multiply*
tengine::create_expression_multiply(
		  detail::node::tvalue_* lhs
		, detail::node::tvalue_* rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);

	LOG_T;

	return create_node(new detail::node::texpression_multiply(lhs, rhs));
}

detail::node::texpression_load*
tengine::create_expression_load(detail::node::tvalue_* lhs)
{
	PRE_CONDITION(lhs);

	LOG_T;

	return create_node(new detail::node::texpression_load(lhs));
}

detail::node::trvalue_variable*
tengine::create_rvalue_variable(detail::node::tqualified_identifier* variable)
{
	PRE_CONDITION(variable);

	LOG_T;

	const detail::symbol::tvariable& symbol
			= symbol_table_.find_variable(*variable);

	return create_node(new detail::node::trvalue_variable(symbol));
}

detail::node::tqualified_identifier*
tengine::create_qualified_identifier(detail::node::tidentifier* identifier)
{
	PRE_CONDITION(identifier);

	LOG_T << "Name " << identifier->name();

	return create_node(new detail::node::tqualified_identifier(identifier));
}

detail::node::tdefinition_integer_variable*
tengine::create_integer_definition(
		  detail::node::tidentifier* variable
		, detail::node::trvalue_integer* value)
{
	PRE_CONDITION(variable);
	PRE_CONDITION(value);

	LOG_T << "Name " << variable->name();

	detail::node::tdefinition_integer_variable* result = create_node(
			new detail::node::tdefinition_integer_variable(variable, value));

	symbol_table_.create_variable(variable->name(), result->get_signature());

	return result;
}

	/***** Symbol. *****/

void
tengine::named_scope_enter(detail::node::tidentifier* name)
{
	PRE_CONDITION(name);

	LOG_T << "Name " << name->name();

	symbol_table_.named_scope_enter(name->name());
}

void
tengine::named_scope_leave()
{
	LOG_T;

	symbol_table_.named_scope_leave();
}

void
tengine::declare_method(
		  detail::node::tidentifier* name
		, detail::node::targument_list* argument_list)
{
	PRE_CONDITION(name);
	PRE_CONDITION(argument_list);

	LOG_T << "Name " << name->name();

	detail::node::tstatement_list statement_list;
	detail::node::tdefinition_method method(
			  symbol_table_.current_scope()
			, name
			, argument_list
			, &statement_list);

	symbol_table_.create_method(name->name(), method.get_signature(), false);

	if(name->name() == "main") {
		if(!main_signature_.empty()) {
			throw exception::tredefinition(
				"There may only be one main function declared.\n");
		}

		main_signature_ = method.get_signature();
	}
}

} // namespace compiler
