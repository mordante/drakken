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
 * Contains the variables for the symbol table.
 *
 * @note This class will be refactored later.
 */

#ifndef MODULES_COMPILER_DETAIL_SYMBOL_VARIABLE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_SYMBOL_VARIABLE_HPP_INCLUDED

#include <string>

namespace compiler {
namespace detail {
namespace symbol {

struct tnamed_scope;

struct tvariable
{
	/** Points to the named scope in which the variable is defined. */
	tnamed_scope& parent;

	/** The signature of the variable. */
	std::string signature;
};

} // namespace symbol
} // namespace detail
} // namespace compiler

#endif
