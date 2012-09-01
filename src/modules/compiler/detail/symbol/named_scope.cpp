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

#include "modules/compiler/detail/symbol/named_scope.hpp"

namespace compiler {
namespace detail {
namespace symbol {

tnamed_scope::tnamed_scope(tnamed_scope* parent__, const std::string& name__)
	: parent(parent__)
	, name_(name__)
	, signature_()
{
	tnamed_scope* itor = this;
	do {
		signature_ = itor->name_ + "^" + signature_;
	} while((itor = itor->parent));
#if 0
	if(name_.empty()) {
		assert(!parent);
		return;
	}

	signature_ =  "::" + name_ + "::";

	tnamed_scope* itor = parent;
	do {
		signature_ = "::" + itor->name_ + signature_;
	} while((itor = itor->parent));
#endif
}

const std::string&
tnamed_scope::signature() const
{
	return signature_;
}

} // namespace symbol
} // namespace detail
} // namespace compiler
