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

#include "modules/compiler/detail/node/rvalue_integer.hpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {

trvalue_integer::trvalue_integer(const int value)
	: value_(value)
{
}

void
trvalue_integer::generate_code(std::ostream& output)
{
	output << '#' << std::hex << value_;
}

void
trvalue_integer::load(std::ostream& output, const std::string& reg)
{
	/**
	 * @todo Evaluate the size of the value:
	 * * <=2 bytes; Use move.
	 * * <=3 bytes; Use push and pop.
	 * *  =4 bytes; Need to store the value in the binary and retreive it.
	 */
	output << "\tpush\t\t";
	generate_code(output);
	output << '\n';
	output << "\tpop\t\t" << reg << '\n';
}

int
trvalue_integer::value() const
{
	return value_;
}

} // namespace node
} // namespace detail
} // namespace compiler
