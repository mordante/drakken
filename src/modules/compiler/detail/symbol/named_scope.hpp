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
 * Contains the named scope for the symbol table.
 *
 * @todo Polish this file.
 */

#ifndef MODULES_COMPILER_DETAIL_SYMBOL_NAMED_SCOPE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_SYMBOL_NAMED_SCOPE_HPP_INCLUDED

#include "modules/compiler/detail/symbol/procedure.hpp"
#include "modules/compiler/detail/symbol/variable.hpp"

#include <map>
#include <string>

namespace compiler {
namespace detail {
namespace symbol {

struct tnamed_scope
{
	tnamed_scope(tnamed_scope* parent__, const std::string& name__);

	const std::string&
	signature() const;

	tnamed_scope* parent;

	/** The child named scope. */
	std::map<std::string /* name */, tnamed_scope> named_scopes;

	/** The procedures in the named scope. */
	std::multimap<std::string /* name */, tprocedure> procedures;

	/** The variables in the named scope. */
	std::multimap<std::string /* name */, tvariable> variables;

private:

	/** The name of the scope. */
	const std::string name_;

	std::string signature_;
};

} // namespace symbol
} // namespace detail
} // namespace compiler

#endif
