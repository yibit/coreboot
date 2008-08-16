/*
 * This file is part of the coreboot project
 *
 * Copyright(C) 2007 coresystems GmbH
 * Written by Stefan Reinauer <stepan@coresystems.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef SHARED_H
#define SHARED_H

#define FUNC(func, ret, attr, args...)   \
	ret func(args) attr
#define EXTERN(func, ret, attr, args...)

/**
 * Use the SHARED macro to create a universally usable function 
 * prototype. This will create a function prototype in stage 0 and
 * a function prototype plus a function pointer for all code compiled
 * with _SHARED defined (required for XIP code)
 *
 * @func   function name
 * @ret    return value
 * @args   function arguments
 */

#define SHARED(func,ret,args...) \
	FUNC(func,ret,,##args);  \
	EXTERN(func,ret,,##args)


/**
 * Use the SHARED_WITH_ATTRIBUTES macro to create a universally usable function 
 * prototype for a function using GCC attributes. 
 * This macro works identically to SHARED(), but it adds a GCC attribute to the
 * function. So far we use this to have printk parameters tested with a
 * "format" attribute.
 *
 * @func   function name
 * @ret    return value
 * @attr   function attributes
 * @args   function arguments
 */

#define SHARED_WITH_ATTRIBUTES(func,ret,attr,args...) \
	FUNC(func,ret,attr,##args);  \
	EXTERN(func,ret,attr,##args)

#endif /* SHARED_H */
