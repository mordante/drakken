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
 * Defines several validation and failure macros.
 *
 * The macros all throw a descendant of @ref lib::texception upon failure or
 * allows the user to select an exception to throw.
 */

#ifndef LIB_UTILITY_VALIDATE_TPP_INCLUDED
#define LIB_UTILITY_VALIDATE_TPP_INCLUDED

#include "lib/exception/exception.hpp"
#include "lib/utility/concatenate.tpp"

/**
 * Validates whether the @p condition is true.
 *
 * This function is intended to replace @c std::assert(condition).
 *
 * @pre                           @p exception has a constructor accepting a
 *                                @c std::string as single parameter. (The
 *                                constructor is called explicitly.)
 * @pre                           @p condition can be evaluated as a boolean
 *                                expression.
 *
 * @param exception               The exception to throw upon failure.
 * @param condition               The condition to validate. It the condition
 *                                evaluates to @c true, nothing happens, if it
 *                                evaluates to @c false an exception of the
 *                                type @p exception is thrown.
 */
#define VALIDATE(exception, condition)                                       \
	do {                                                                     \
		if(!(condition)) {                                                   \
			throw exception(::lib::concatenate(                              \
					  "Conditional failure in function '"                    \
					, __PRETTY_FUNCTION__                                    \
					, "' file '"                                             \
					, __FILE__                                               \
					, "' line '"                                             \
					, __LINE__                                               \
					, "' condition '"                                        \
					, #condition                                             \
					, "'"));                                                 \
		}                                                                    \
	} while(0)


/**
 * Validates whether the pre condition @p condition is true.
 *
 * This function is intended to replace @c std::assert(condition).
 *
 * @pre                           @p condition can be evaluated as a boolean
 *                                expression.
 *
 * @param condition               The condition to validate. It the condition
 *                                evaluates to @c true, nothing happens, if it
 *                                evaluates to @c false an exception of the
 *                                type @ref lib::tpre_condition is thrown.
 */
#define PRE_CONDITION(condition)                                             \
	do {                                                                     \
		if(!(condition)) {                                                   \
			throw ::lib::tpre_condition(::lib::concatenate(                  \
					  "Conditional failure in function '"                    \
					, __PRETTY_FUNCTION__                                    \
					, "' file '"                                             \
					, __FILE__                                               \
					, "' line '"                                             \
					, __LINE__                                               \
					, "' condition '"                                        \
					, #condition                                             \
					, "'"));                                                 \
		}                                                                    \
	} while(0)

/**
 * Validates whether the assertion @p condition is true.
 *
 * This function is intended to replace @c std::assert(condition).
 *
 *                                @c std::string as single parameter.
 * @pre                           @p condition can be evaluated as a boolean
 *                                expression.
 *
 * @param condition               The condition to validate. It the condition
 *                                evaluates to @c true, nothing happens, if it
 *                                evaluates to @c false an exception of the
 *                                type @ref lib::tassertion is thrown.
 */
#define ASSERTION(condition)                                                 \
	do {                                                                     \
		if(!(condition)) {                                                   \
			throw ::lib::tassertion(::lib::concatenate(                      \
					  "Conditional failure in function '"                    \
					, __PRETTY_FUNCTION__                                    \
					, "' file '"                                             \
					, __FILE__                                               \
					, "' line '"                                             \
					, __LINE__                                               \
					, "' condition '"                                        \
					, #condition                                             \
					, "'"));                                                 \
		}                                                                    \
	} while(0)

#endif
