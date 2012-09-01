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

#include "modules/compiler/exception.hpp"

namespace compiler {
namespace exception {

texception::texception(const std::string& message)
	: lib::texception(message)
{
}

tredefinition::tredefinition(const std::string& message)
	: texception(message)
{
}

tundefined::tundefined(const std::string& message)
	: texception(message)
{
}

tunimplemented::tunimplemented(const std::string& message)
	: texception(message)
{
}

} // namespace exception
} // namespace compiler
