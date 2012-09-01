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
 * Contains emulation for the C++11 feature:
 * @code for(auto foo : bar) @endcode.
 * The code is based upon Boost bug report
 * https://svn.boost.org/trac/boost/ticket/3643 and uses BOOST_FOREACH
 * and BOOST_TYPEOF internally.
 */

#ifndef LIB_UTILITY_FOREACH_TPP_INCLUDED
#define LIB_UTILITY_FOREACH_TPP_INCLUDED

#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

#define FOREACH(VAR, RANGE) \
	BOOST_FOREACH(BOOST_TYPEOF(*boost::begin(RANGE)) VAR, RANGE)

#endif
