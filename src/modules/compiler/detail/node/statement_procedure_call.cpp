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

#include "modules/compiler/detail/node/statement_procedure_call.hpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {

tstatement_procedure_call::tstatement_procedure_call(
		  const std::string& signature)
	: signature_(signature)
{
}

void
tstatement_procedure_call::generate_code(std::ostream& output)
{
	output << "\tcall\t\t" << signature_ << '\n';
}

} // namespace node
} // namespace detail
} // namespace compiler
