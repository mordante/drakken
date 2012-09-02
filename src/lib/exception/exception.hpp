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
 * Contains the exceptions hierarchy for the drakken suite.
 *
 * Some of the base classes can't be thrown, they are only around to provide
 * nodes in the hierarchy. These nodes use protected constructors to avoid
 * being created directly.
 */

#ifndef LIB_EXCEPTION_EXCEPTION_HPP_INCLUDED
#define LIB_EXCEPTION_EXCEPTION_HPP_INCLUDED

#include <string>

namespace lib {

/**
 * The base class for all VM exceptions.
 *
 * @note The exception isn't throw directly, but one of the classes inheriting
 * this exception will.
 */
class texception
	: public std::exception
{
protected:

	texception(const std::string& message);

public:

	virtual ~texception() throw();

	virtual const char* what() const throw();

private:

	std::string message_;
};

/** Thrown when a pre-condition is violated. */
struct tpre_condition
	: public texception
{
	tpre_condition(const std::string& message);
};

/** Thrown when an assertion is violated. */
struct tassertion
	: public texception
{
	tassertion(const std::string& message);
};

/** Thrown when a post-condition is violated. */
struct tpost_condition
	: public texception
{
	tpost_condition(const std::string& message);
};

/** Thrown when the wanted functionality has not yet been implemented. */
struct tunimplemented
	: public texception
{
	tunimplemented(const std::string& message);
};

} // namespace lib

#endif
