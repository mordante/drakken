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
 * The main file for the drakken program.
 */

#include "lib/utility/log.tpp"

int
main()
{
	google::InitGoogleLogging("drakken");
	FLAGS_v = 2;

#ifdef GLOG_HAS_LOG_PREFIX_FORMAT
	FLAGS_log_prefix_format
			= "%s %y%m%dT%H%M%S.%U %f:%l%c(severity based info)] ";
#endif

	LOG_I << "Starting program";

	LOG_I << "Finishing program";
}
