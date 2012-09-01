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
 * Helper file for inclusion of the all node sub-headers.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_HPP_INCLUDED

#include "modules/compiler/detail/node/argument_list.hpp"
#include "modules/compiler/detail/node/definition_integer_variable.hpp"
#include "modules/compiler/detail/node/definition_method.hpp"
#include "modules/compiler/detail/node/expression_binary_operation.hpp"
#include "modules/compiler/detail/node/expression_unary_operation.hpp"
#include "modules/compiler/detail/node/identifier.hpp"
#include "modules/compiler/detail/node/node.hpp"
#include "modules/compiler/detail/node/nop.hpp"
#include "modules/compiler/detail/node/program.hpp"
#include "modules/compiler/detail/node/qualified_identifier.hpp"
#include "modules/compiler/detail/node/rvalue_integer.hpp"
#include "modules/compiler/detail/node/rvalue_string.hpp"
#include "modules/compiler/detail/node/rvalue_variable.hpp"
#include "modules/compiler/detail/node/statement_assign.hpp"
#include "modules/compiler/detail/node/statement_list.hpp"
#include "modules/compiler/detail/node/statement_procedure_call.hpp"
#include "modules/compiler/detail/node/value.hpp"

namespace compiler {
namespace detail {

/**
 * Generic nop node.
 *
 * Since the nop node doesn't generate code all nop generating functions can
 * return a pointer to this object so save some memory.
 */
extern node::tnop nop;

} // namespace detail
} // namespace compiler

#endif
