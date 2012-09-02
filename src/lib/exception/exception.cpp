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

#include "lib/exception/exception.hpp"

namespace lib {

texception::texception(const std::string& message)
	: message_(message)
{
}

texception::~texception() throw()
{
}

const char*
texception::what() const throw()
{
	return message_.c_str();
}


tpre_condition::tpre_condition(const std::string& message)
	: texception(message)
{
}

tassertion::tassertion(const std::string& message)
	: texception(message)
{
}

tpost_condition::tpost_condition(const std::string& message)
	: texception(message)
{
}

tunimplemented::tunimplemented(const std::string& message)
	: texception(message)
{
}

} // namespace lib
