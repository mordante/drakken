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
 * Contains the symbol table.
 *
 * @todo Improve this file.
 */

#ifndef MODULES_COMPILER_DETAIL_SYMBOL_TABLE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_SYMBOL_TABLE_HPP_INCLUDED

#include "modules/compiler/detail/symbol/named_scope.hpp"

#include <string>
#include <vector>

namespace compiler {
namespace detail {
namespace node {

class tqualified_identifier;

} // namespace node

namespace symbol {

class tsymbol_table
{
public:

	tsymbol_table();

	void
	named_scope_enter(const std::string& name);

	void
	named_scope_leave();

	/**
	 * Validates the symbol table.
	 *
	 * At the moment it only tests whether all declared procedures are also
	 * defined.
	 */
	void
	validate() const;

	/**
	 * Creates a new method in the current scope.
	 *
	 * A method may only be defined once, but can be declared before being
	 * defined. It is also not yet specified whether it is allowed to
	 * declare a method more than once.
	 *
	 * @param name                The name of the method.
	 * @param signature           The signature of the method.
	 * @param definition          Is the call placed from a definition.
	 */
	void
	create_method(
			  const std::string& name
			, const std::string& signature
			, const bool definition);

	void
	create_variable(const std::string& name, const std::string& signature);

	const tprocedure&
	find_method(const std::string& name) const;

	const tprocedure&
	find_method(const node::tqualified_identifier& identifier) const;

	const tvariable&
	find_variable(const node::tqualified_identifier& identifier) const;

	const tnamed_scope&
	current_scope() const;

private:

	tnamed_scope global_scope_;

	tnamed_scope* current_scope_;
};

} // namespace symbol
} // namespace detail
} // namespace compiler

#endif

