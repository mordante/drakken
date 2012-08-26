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
 * Contains the logging macros.
 *
 * The real logging is done by the Google glog library, these wrappers are for
 * convenience only.
 */

#ifndef LIB_UTILITY_LOG_TPP_INCLUDED
#define LIB_UTILITY_LOG_TPP_INCLUDED

#include <glog/logging.h>

#ifdef GLOG_HAS_LOG_PREFIX_FORMAT
	#define LOG_F LOG(FATAL) << "] "
	#define LOG_E LOG(ERROR) << "] "
	#define LOG_W LOG(WARNING) << "] "
	#define LOG_I LOG(INFO) << "] "
	#ifdef __GNUG__
		#define LOG_D VLOG(1) << " `" << __PRETTY_FUNCTION__ << "' DEBUG] "
		#define LOG_T VLOG(2) << " `" << __PRETTY_FUNCTION__ << "' TRACE] "
	#else
		#define LOG_D VLOG(1) << " `" << __FUNCTION__ << "' DEBUG] "
		#define LOG_T VLOG(2) << " `" << __FUNCTION__ << "' TRACE] "
	#endif
#else
	#define LOG_F LOG(FATAL)
	#define LOG_E LOG(ERROR)
	#define LOG_W LOG(WARNING)
	#define LOG_I LOG(INFO)
	#ifdef __GNUG__
		#define LOG_D VLOG(1) << "`" << __PRETTY_FUNCTION__ << "' DEBUG] "
		#define LOG_T VLOG(2) << "`" << __PRETTY_FUNCTION__ << "' TRACE] "
	#else
		#define LOG_D VLOG(1) << "`" << __FUNCTION__ << "' DEBUG] "
		#define LOG_T VLOG(2) << "`" << __FUNCTION__ << "' TRACE] "
	#endif
#endif

#endif
