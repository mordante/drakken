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

/**
 * @file
 * Contains the compiler engine.
 */

#ifndef MODULES_COMPILER_ENGINE_HPP_INCLUDED
#define MODULES_COMPILER_ENGINE_HPP_INCLUDED

#include "modules/compiler/detail/node.hpp"
#include "modules/compiler/detail/symbol/table.hpp"

#include <deque>
#include <iosfwd>
#include <set>

namespace compiler {

class tengine
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @param output              Initialises @ref output_.
	 * @param input               Initialises @ref input.
	 */
	tengine(std::ostream& output, std::istream& input);

	~tengine();


	/***** ***** Operations. ***** *****/

	/***** Generic. *****/

	/**
	 * Runs the compiler.
	 *
	 * It reads the @ref input and stores its result in the @ref output_.
	 * When it encounters a problem it throws an exception.
	 *
	 * @warning @ref run() may only be called once, calling it multiple times
	 * with the same object leads to undefined behaviour.
	 *
	 * @pre                       @ref program_ == @c NULL
	 */
	void
	run();

	/**
	 * Sets the debug mode for flex.
	 *
	 * Flex is used for the lexical analyser of the compiler. This function
	 * can enable or disable its debug output.
	 *
	 * @note The function is implemented in
	 * @e modules/compiler/detail/lexer.l.
	 *
	 * @param state               Enable or disable the debug mode.
	 */
	void
	set_flex_debug(const bool state);


	/***** Lexer node. *****/

	/**
	 * Creates an integer rvalue node.
	 *
	 * @param value               The value for the rvalue.
	 *
	 * @returns                   The created node.
	 */
	detail::node::trvalue_integer*
	create_rvalue_integer(const int value);

	/**
	 * Creates a string rvalue node.
	 *
	 * @param value               The value for the rvalue.
	 *
	 * @returns                   The created node.
	 */
	detail::node::trvalue_string*
	create_rvalue_string(const std::string& value);

	/**
	 * Creates an identifier node.
	 *
	 * @param name                The name of the identifier.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tidentifier*
	create_identifier(const std::string& name);


	/***** Parser node. *****/

	/**
	 * Creates a program node.
	 *
	 * @pre                       @p interface != @c NULL
	 * @pre                       @p implementation != @c NULL
	 * @pre                       @ref program_ == @c NULL
	 *
	 * @post                      @ref program_ != @c NULL
	 *
	 * @param interface           Forwarded to
	 *                            @ref detail::node::tprogram::tprogram().
	 * @param implementation      Forwarded to
	 *                            @ref detail::node::tprogram::tprogram().
	 *
	 * @returns                   The created node.
	 */
	detail::node::tprogram*
	create_program(
			  detail::node::tnode_* interface
			, detail::node::tnode_* implementation);

	/**
	 * Creates a statement list node.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tstatement_list*
	create_statement_list();

	/**
	 * Creates an argument list node.
	 *
	 * @returns                   The created node.
	 */
	detail::node::targument_list*
	create_argument_list();

	/**
	 * Creates a method definition node.
	 *
	 * @pre                       @p name != @c NULL
	 * @pre                       @p argument_list != @c NULL
	 * @pre                       @p statement_list != @c NULL
	 *
	 * @param name                The name of the method to declare.
	 * @param argument_list       The arguments for the method.
	 * @param statement_list      A list with zero or more statements to
	 *                            execute in the method.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tdefinition_method*
	create_definition_method(
			  detail::node::tidentifier* name
			, detail::node::targument_list* argument_list
			, detail::node::tnode_* statement_list);

	/**
	 * Create an assign statement node.
	 *
	 * @pre                       @p lhs != @c NULL
	 * @pre                       @p rhs != @c NULL
	 *
	 * @param lhs                 Forwarded to @ref
	 * detail::node::tstatement_assign::tstatement_assign().
	 *
	 * @param rhs                 Forwarded to @ref
	 * detail::node::tstatement_assign::tstatement_assign().
	 *
	 *
	 * @returns                   The created node.
	 */
	detail::node::tstatement_assign*
	create_statement_assign(
			  detail::node::tidentifier* lhs
			, detail::node::tnode_* rhs);

	/**
	 * Create a procedure call statement node.
	 *
	 * @pre                       @p procedure != @c NULL
	 *
	 * @param procedure           The (fully-)qualified identifier
	 *                            identifying the procedure to call.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tstatement_procedure_call*
	create_statement_procedure_call(
			  detail::node::tqualified_identifier* procedure);

	/**
	 * Create an add expression node.
	 *
	 * @pre                       @p lhs != @c NULL
	 * @pre                       @p rhs != @c NULL
	 *
	 * @param lhs                 Forwarded to @ref
	 * detail::node::texpression_add::texpression_add().
	 *
	 * @param rhs                 Forwarded to @ref
	 * detail::node::texpression_add::texpression_add().
	 *
	 *
	 * @returns                   The created node.
	 */
	detail::node::texpression_add*
	create_expression_add(
			  detail::node::tvalue_* lhs
			, detail::node::tvalue_* rhs);

	/**
	 * Create a subtract expression node.
	 *
	 * @pre                       @p lhs != @c NULL
	 * @pre                       @p rhs != @c NULL
	 *
	 * @param lhs                 Forwarded to @ref
	 * detail::node::texpression_subtract::texpression_subtract().
	 *
	 * @param rhs                 Forwarded to @ref
	 * detail::node::texpression_subtract::texpression_subtract().
	 *
	 *
	 * @returns                   The created node.
	 */
	detail::node::texpression_subtract*
	create_expression_subtract(
			  detail::node::tvalue_* lhs
			, detail::node::tvalue_* rhs);

	/**
	 * Create a multiply expression node.
	 *
	 * @pre                       @p lhs != @c NULL
	 * @pre                       @p rhs != @c NULL
	 *
	 * @param lhs                 Forwarded to @ref
	 * detail::node::texpression_multiply::texpression_multiply().
	 *
	 * @param rhs                 Forwarded to @ref
	 * detail::node::texpression_multiply::texpression_multiply().
	 *
	 *
	 * @returns                   The created node.
	 */
	detail::node::texpression_multiply*
	create_expression_multiply(
			  detail::node::tvalue_* lhs
			, detail::node::tvalue_* rhs);

	/**
	 * Create a load expression node.
	 *
	 * @pre                       @p lhs != @c NULL
	 *
	 * @param lhs                 Forwarded to @ref
	 * detail::node::texpression_load::texpression_load().
	 *
	 *
	 * @returns                   The created node.
	 */
	detail::node::texpression_load*
	create_expression_load(detail::node::tvalue_* lhs);

	/**
	 * Create a variable rvalue node.
	 *
	 * @pre                       @p variable != @c NULL
	 *
	 * @param variable            The (fully-)qualified identifier
	 *                            identifying the variable to use as rvalue.
	 *
	 * @returns                   The created node.
	 */
	detail::node::trvalue_variable*
	create_rvalue_variable(detail::node::tqualified_identifier* variable);

	/**
	 * Create a qualified identifier node.
	 *
	 * @pre                       @p identifier != @c NULL
	 *
	 * @param identifier          The final identifier for a qualified
	 *                            identifier. The other parts of the
	 *                            qualification will be added later to the
	 *                            created object.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tqualified_identifier*
	create_qualified_identifier(detail::node::tidentifier* identifier);


	/**
	 * Create a integer definition node.
	 *
	 * @pre                       @p variable != @c NULL
	 * @pre                       @p value != @c NULL
	 *
	 * @param variable            The (fully-)qualified identifier
	 *                            identifying the variable to be created.
	 * @param value               The value to assign to the variable being
	 *                            created.
	 *
	 * @returns                   The created node.
	 */
	detail::node::tdefinition_integer_variable*
	create_integer_definition(
			  detail::node::tidentifier* variable
			, detail::node::trvalue_integer* value);


	/***** Symbol. *****/

	/**
	 * Enters a named scope.
	 *
	 * When the scope exists it is reopened, if not it is created and
	 * entered. This is like the namespaces in C++.
	 *
	 * Calls to this function should be paired with calls to
	 * @ref named_scope_leave().
	 *
	 * @pre                       @p name != @c NULL
	 *
	 * @param name                The identifier holding the name of the
	 *                            scope to enter.
	 */
	void
	named_scope_enter(detail::node::tidentifier* name);

	/**
	 * Leaves the current named scope.
	 *
	 * Calls to this function should be paired with calls to
	 * @ref named_scope_enter().
	 */
	void
	named_scope_leave();

	/**
	 * Declares a method.
	 *
	 * When a method is declared it adds an entry to the symbol table.
	 *
	 * @note When a function is declared it also needs to be defined.
	 *
	 * @pre                       @p name != @c NULL
	 * @pre                       @p argument_list != @c NULL
	 *
	 * @param name                The name of the method to declare.
	 * @param argument_list       The arguments for the method.
	 */
	void
	declare_method(
			  detail::node::tidentifier* name
			, detail::node::targument_list* argument_list);


	/***** ***** Members. ***** *****/

	/**
	 * Helper for the scanner engine.
	 *
	 * The variable is handled by @e modules/compiler/detail/lexer.l.
	 */
	void* scanner;

	/**
	 * Helper for the scanner engine.
	 *
	 * The variable is directly used by @e modules/compiler/detail/lexer.l.
	 */
	std::istream& input;

private:

	/** The output to write the compiler output to. */
	std::ostream& output_;

	/**
	 * String table for all identifiers used.
	 *
	 * Since the @ref detail::node::tidentifier nodes only keep a reference
	 * to their name it needs to be stored in a fixed location. The set keeps
	 * them.
	 *
	 * @note There are two demands on the data container:
	 * - Insert doesn't invalidate reference to existing nodes.
	 * - Quick lookup identical values, to avoid storing multiple copies.
	 */
	std::set<std::string> identifiers_;

	/**
	 * String table for all strings used.
	 *
	 * Similar to @ref identifiers_ but then for the string rvalues.
	 *
	 * @note This object might be merged with @ref identifiers_ since both
	 * only keeps track of immutable values.
	 */
	std::set<std::string> strings_;

	/**
	 * The storage pool for all nodes created.
	 *
	 * Due to the design used in Bison, we need to `return' the pointers to
	 * created nodes in a union. In order to keep track of all allocated
	 * objects this pool stores all allocated object. This allows our
	 * destructor to destroy the objects.
	 *
	 * @note There is only one main requirement for the pool, keep track of
	 * the memory and do it efficiently. A vector can have a small space
	 * overhead, but since it needs to keep the memory contiguous will have
	 * overhead upon resizing (both in time and space). The deque also has a
	 * small space overhead and doesn't move its contents upon resizing.
	 */
	std::deque<detail::node::tnode_*> nodes_;

	/**
	 * Pointer to the program node.
	 *
	 * This node is the root of the AST so needs to be easily found.
	 */
	detail::node::tprogram* program_;

	/** The symbol table of the engine. */
	detail::symbol::tsymbol_table symbol_table_;

	/**
	 * The signature of the main function or method.
	 */
	std::string main_signature_;

	/**
	 * Wrapper for `creating' nodes.
	 *
	 * The wrapper makes sure the newly allocated node is stored in the node
	 * pool; @ref nodes_.
	 *
	 * @pre                       @p node != @c NULL
	 *
	 * @param node                A newly created node.
	 *
	 * @returns                   @p node.
	 */
	template<class T>
	T
	create_node(T node)
	{
		nodes_.push_back(node);
		return node;
	}

	/**
	 * Initialises the @ref scanner.
	 *
	 * @note The function is implemented in
	 * @e modules/compiler/detail/lexer.l.
	 */
	void init_scanner();

	/**
	 * Destroys the @ref scanner.
	 *
	 * @note The function is implemented in
	 * @e modules/compiler/detail/lexer.l.
	 */
	void destroy_scanner();

};

} // namespace compiler

#endif
