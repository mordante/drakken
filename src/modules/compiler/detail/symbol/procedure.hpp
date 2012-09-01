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
 * Contains the procedures for the symbol table.
 *
 * @note This class will be refactored later.
 */

#ifndef MODULES_COMPILER_DETAIL_SYMBOL_PROCEDURE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_SYMBOL_PROCEDURE_HPP_INCLUDED

#include <string>

namespace compiler {
namespace detail {
namespace symbol {

struct tnamed_scope;

struct tprocedure
{
	tnamed_scope& parent;

	/** The signature of the element. */
	std::string signature;

	/** Whether or not the element is defined, or only declared. */
	bool defined;
};

} // namespace symbol
} // namespace detail
} // namespace compiler

#endif

