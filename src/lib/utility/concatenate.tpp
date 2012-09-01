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
 * Helper library to concatenate various types to a string.
 *
 * The code is inspired on similar code written using C++11. That version uses
 * variadic templates.
 */

#ifndef LIB_UTILITY_CONCATENATE_TPP_INCLUDED
#define LIB_UTILITY_CONCATENATE_TPP_INCLUDED

#include <sstream>

namespace lib {

/**
 * Concatenates a list of variables to a string.
 *
 * It uses the operator<<() for all variables.
 *
 * @note When there are more parameters required as defined here it is trivial
 * to add extra versions of the function.
 *
 * @tparam T1...TN                The parameter types to convert to a string.
 *
 * @param p1...pN                 The parameters to convert to a string.
 *
 * @returns                       The concatenated string.
 */
template<
	  class T1
	>
inline std::string
concatenate(
		  const T1& p1
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	, class T5
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		, const T5& p5
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		<< p5
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	, class T5
	, class T6
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		, const T5& p5
		, const T6& p6
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		<< p5
		<< p6
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	, class T5
	, class T6
	, class T7
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		, const T5& p5
		, const T6& p6
		, const T7& p7
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		<< p5
		<< p6
		<< p7
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	, class T5
	, class T6
	, class T7
	, class T8
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		, const T5& p5
		, const T6& p6
		, const T7& p7
		, const T8& p8
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		<< p5
		<< p6
		<< p7
		<< p8
		;
	return sstr.str();
}

template<
	  class T1
	, class T2
	, class T3
	, class T4
	, class T5
	, class T6
	, class T7
	, class T8
	, class T9
	>
inline std::string
concatenate(
		  const T1& p1
		, const T2& p2
		, const T3& p3
		, const T4& p4
		, const T5& p5
		, const T6& p6
		, const T7& p7
		, const T8& p8
		, const T9& p9
		)
{
	std::stringstream sstr;
	sstr
		<< p1
		<< p2
		<< p3
		<< p4
		<< p5
		<< p6
		<< p7
		<< p8
		<< p9
		;
	return sstr.str();
}

} // namespace lib

#endif
