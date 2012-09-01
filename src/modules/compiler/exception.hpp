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
 * Contains the exceptions hierarchy for the compiler library.
 *
 * Some of the base classes can't be thrown, they are only around to provide
 * nodes in the hierarchy. These nodes use protected constructors to avoid
 * being created directly.
 */

#ifndef MODULES_COMPILER_EXCEPTION_HPP_INCLUDED
#define MODULES_COMPILER_EXCEPTION_HPP_INCLUDED

#include "lib/exception/exception.hpp"

namespace compiler {
namespace exception {

/**
 * The base class for all VM exceptions.
 *
 * @note The exception isn't thrown directly, but one of the classes inheriting
 * this exception will.
 */
class texception
	: public lib::texception
{
protected:

	texception(const std::string& message);
};

/** Thrown when an object is defined twice. */
struct tredefinition
	: public texception
{
	tredefinition(const std::string& message);
};

/**
 * Thrown when an item is undefined.
 */
struct tundefined
	: public texception
{
	tundefined(const std::string& message);
};

/** Thrown when the wanted functionality has not yet been implemented. */
struct tunimplemented
	: public texception
{
	tunimplemented(const std::string& message);
};

} // namespace exception
} // namespace compiler

#endif
