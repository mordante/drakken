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


#include "modules/compiler/detail/symbol/table.hpp"

#include "lib/utility/foreach.tpp"
#include "lib/utility/validate.tpp"
#include "modules/compiler/exception.hpp"
#include "modules/compiler/detail/node/identifier.hpp"
#include "modules/compiler/detail/node/qualified_identifier.hpp"

#include <cassert>

namespace compiler {
namespace detail {
namespace symbol {

tsymbol_table::tsymbol_table()
	: global_scope_(NULL, "")
	, current_scope_(&global_scope_)
{
}

void
tsymbol_table::named_scope_enter(const std::string& name)
{
	// get current scope
	// add the new one if doesn't exist
	// enter the scope
	PRE_CONDITION(current_scope_);
#if 0
	typedef std::pair<std::string, tnamed_scope> thack_namespace;
	BOOST_FOREACH(thack_namespace& ns, current_namespace_->namespaces) {
		if(ns.first == name) {
			current_namespace_ = &ns.second;
			return;
		}
	}
#endif
	current_scope_
			= &current_scope_->named_scopes.insert(
				  std::make_pair(name, tnamed_scope(current_scope_, name))
				).first->second;
}

void
tsymbol_table::named_scope_leave()
{
	// validate the current layer is a scope
	// leave it
	PRE_CONDITION(current_scope_);
	PRE_CONDITION(current_scope_->parent);

	current_scope_ = current_scope_->parent;
}

static void
validate_named_scope(const tnamed_scope& ns)
{
	FOREACH(const& procedure, ns.procedures) {
		if(!procedure.second.defined) {
			throw exception::tundefined(lib::concatenate(
					  "Procedure »"
					, procedure.second.signature
					, "« is declared but not defined."));
		}
	}

	FOREACH(const& item, ns.named_scopes) {
		validate_named_scope(item.second);
	}
}

void
tsymbol_table::validate() const
{
	validate_named_scope(global_scope_);
}

void
tsymbol_table::create_method(
		  const std::string& name
		, const std::string& signature
		, const bool definition)
{
	PRE_CONDITION(current_scope_);

//	BOOST_AUTO(const procedures, layers_.back().elements.equal_range(name));
//	for(BOOST_AUTO(itor, elements.first); itor != elements.second; ++itor) {

	BOOST_AUTO(
			  const procedures
			, current_scope_->procedures.equal_range(name));

	for(BOOST_AUTO(itor, procedures.first); itor != procedures.second; ++itor) {

		if(/*itor->second.type == telement::method
				&& */itor->second.signature == signature) {

			if(itor->second.defined) {
				if(definition) {
					throw exception::tredefinition(lib::concatenate(
							  "Method »"
							, name
							, "« was defined as »"
							, itor->second.signature
							, "« is redefined."));
				} else {
					throw exception::tredefinition(lib::concatenate(
							  "Method »"
							, name
							, "« was defined as »"
							, itor->second.signature
							, "« is redeclared."));
				}
			} else {
				if(definition) {
					itor->second.defined = true;
				} else {
					throw exception::tredefinition(lib::concatenate(
							  "Method »"
							, name
							, "« was declared as »"
							, itor->second.signature
							, "« is redeclared."));
				}
			}
		}
	}

	tprocedure procedure = { *current_scope_, signature, definition };
	current_scope_->procedures.insert(std::make_pair(name, procedure));
}

void
tsymbol_table::create_variable(
		  const std::string& name
		, const std::string& signature)
{
	assert(current_scope_);

	/**
	 * @todo Validate whether at a namespace or in a scope.
	 *
	 * Depending on the result the variable needs to be stored differently.
	 */

	BOOST_AUTO(
			  const variables
			, current_scope_->variables.equal_range(name));

	for(BOOST_AUTO(itor, variables.first); itor != variables.second; ++itor) {
		throw exception::tredefinition(lib::concatenate(
				  "variable »"
				, name
				, "« was defined as »"
				, itor->second.signature
				, "« and is redefined as »"
				, signature
				, "«."));
	}

	tvariable variable = { *current_scope_, signature };
	current_scope_->variables.insert(std::make_pair(name, variable));

/*
	BOOST_AUTO(const elements, layers_.back().elements.equal_range(name));
	for(BOOST_AUTO(itor, elements.first); itor != elements.second; ++itor) {

		if(itor->second.type == telement::global_variable) {
			throw exception::tredefinition(lib::concatenate(
					  "variable »"
					, name
					, "« was defined as »"
					, itor->second.signature
					, "« and is redefined as »"
					, signature
					, "«."));
		}
	}

	telement element = { telement::global_variable, signature, true };
	layers_.back().elements.insert(std::make_pair(name, element));
*/
}

const tprocedure&
tsymbol_table::find_method(const std::string& name) const
{
	assert(current_scope_);

	BOOST_AUTO(
			  const procedures
			, current_scope_->procedures.equal_range(name));

	for(BOOST_AUTO(itor, procedures.first)
			; itor != procedures.second
			; ++itor) {

			return itor->second;
	}

	throw exception::tundefined(lib::concatenate(
			  "Method »"
			, name
			, "« is not defined.\n"));

}

static const tprocedure*
search(tnamed_scope* ns
		, const std::vector<std::string>& named_scopes
		, const std::string& method)
{
	assert(ns);

	/*** First find the named_scope part of the qualified name ***/

	FOREACH(const& scope, named_scopes) {
		BOOST_AUTO(itor, ns->named_scopes.find(scope));
		if(itor == ns->named_scopes.end()) {
			return NULL;
		}

		ns = &itor->second;
	}

	/*** Find the name of the method. ***/

	BOOST_AUTO(itor, ns->procedures.find(method));
	if(itor == ns->procedures.end()) {
		return NULL;
	}

	return &itor->second;
}

const tprocedure&
tsymbol_table::find_method(const node::tqualified_identifier& identifier) const
{
	assert(current_scope_);

	/*** Build the list with the qualified name. ***/

	/*
	 * The result is a list of scopes and the wanted method.
	 */

	std::vector<std::string> scopes;
	FOREACH(const item, identifier.identifiers()) {
		scopes.push_back(item->name());
	}

	assert(!scopes.empty());
	const std::string method = scopes.back();
	scopes.pop_back();

	/*** Try to find the wanted method in all scopes. ***/

	/*
	 * Try to find the result in the current scope. If that fails go to
	 * the parent scope until the global scope has been visited.
	 */

	tnamed_scope* scope = current_scope_;
	do {
		if(const tprocedure* result = search(scope, scopes, method)) {
			return *result;
		}
	} while((scope = scope->parent));

	/*
	 * At this point to lookup failed and we return the proper error.
	 */

	throw exception::tundefined(lib::concatenate(
			  "Method »"
			, method
			, "« is not defined.\n"));
}

static const tvariable*
search_variable(tnamed_scope* named_scope
		, const std::vector<std::string>& scopes
		, const std::string& variable)
{
	assert(named_scope);

	/*** First find the scope part of the qualified name ***/

	FOREACH(const& scope, scopes) {
		BOOST_AUTO(itor, named_scope->named_scopes.find(scope));
		if(itor == named_scope->named_scopes.end()) {
			return NULL;
		}

		named_scope = &itor->second;
	}

	/*** Find the name of the variable. ***/

	BOOST_AUTO(itor, named_scope->variables.find(variable));
	if(itor == named_scope->variables.end()) {
		return NULL;
	}

	return &itor->second;
}

const tvariable&
tsymbol_table::find_variable(
		  const node::tqualified_identifier& identifier) const
{
	assert(current_scope_);

	/*** Build the list with the qualified name. ***/

	/*
	 * The result is a list of scopes and the wanted variable.
	 */

	std::vector<std::string> scopes;
	FOREACH(const item, identifier.identifiers()) {
		scopes.push_back(item->name());
	}

	assert(!scopes.empty());
	const std::string variable = scopes.back();
	scopes.pop_back();

	/*** Try to find the wanted variable in all scopes. ***/

	/*
	 * Try to find the result in the current scope. If that fails go to
	 * the parent scope until the global scope has been visited.
	 */

	tnamed_scope* scope = current_scope_;
	do {
		if(const tvariable* result
				= search_variable(scope, scopes, variable)) {

			return *result;
		}
	} while((scope = scope->parent));

	/*
	 * At this point to lookup failed and we return the proper error.
	 */

	throw exception::tundefined(lib::concatenate(
			  "Variable »"
			, variable
			, "« is not defined.\n"));
}

const tnamed_scope&
tsymbol_table::current_scope() const
{
	assert(current_scope_);
	return *current_scope_;
}

} // namespace symbol
} // namespace detail
} // namespace compiler
