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

#include "modules/compiler/detail/node/program.hpp"

#include "lib/utility/validate.tpp"
#include "modules/compiler/exception.hpp"

#include <iostream>

namespace compiler {
namespace detail {
namespace node {

tprogram::tprogram(
		  tnode_* interface
		, tnode_* implementation
		, const std::string& main_signature)
	: interface_(interface)
	, implementation_(implementation)
	, main_signature_(main_signature)
{
	PRE_CONDITION(interface);
	PRE_CONDITION(implementation);
}

void
tprogram::generate_code(std::ostream& output)
{
	output
			<< "\tversion\t\t#1\n"
			<< "\tjmp\t\tstart\n";

	if(main_signature_.empty()) {
		throw exception::tundefined("No main procedure defined.");
	}

	interface_->generate_code(output);
	implementation_->generate_code(output);

	if(main_signature_ == "method||^main||") {
		output
				<< "start:\n"
				<< "\tcall\t\t" << main_signature_ << '\n'
#if 0
				<< "\tregisters\n"
				<< "\tmemory\t\tvariable|int|answer|\n"
#endif
				<< "\tpush\t\t#0\n"
				<< "\tpop\t\tr0\n"
				<< "\tfinish\n";
	} else {
		throw exception::tundefined(lib::concatenate(
				  "The signature of the main procedure »"
				, main_signature_
				, "« is undefined in the engine.\n"));
	}
}

} // namespace node
} // namespace detail
} // namespace compiler
