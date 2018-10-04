/*
 * Copyright (c) 2000-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * This private header exports 3 APIs.
 *	_OSRosettaCheck() - 	An inline function that returns true if we are
 *				currently running under Rosetta.
 *	IF_ROSETTA() -		Which is used to as a regular conditional
 *				expression that is true only if the current
 *				code is executing in the Rosetta
 *				translation space.
 *	ROSETTA_ONLY(exprs) - 	Which is used to create a block code that only
 *				executes if we are running in Rosetta.
 *
 * for example
 *
 * IF_ROSETTA() {
 *	// Do Cross endian swapping of input data
 *	outdata = OSSwap??(indata);
 * }
 * else {
 * 	// Do straight through 
 *	outdata = indata;
 * }
 *
 * outdata = indata;
 * ROSETTA_ONLY(
 *	// Do Cross endian swapping of input data
 *	outdata = OSSwap??(outdata);
 * );
 */

#ifndef _LIBKERN_OSCROSSENDIAN_H
#define _LIBKERN_OSCROSSENDIAN_H

#if __ppc__

static __inline__ int _OSRosettaCheck(void)
{
    int isCrossEndian;

    __asm__ (  "b 0f\n"
	    "	.long 0x14400004\n"
	    "	li %0,1\n"
	    "0:"
	: "=r" (isCrossEndian) : "0" (0)
    );

    return isCrossEndian;
}

#else

static __inline__ int _OSRosettaCheck(void) { return 0; }

#endif

#define IF_ROSETTA() if (__builtin_expect(_OSRosettaCheck(), 0) )

#define ROSETTA_ONLY(exprs)	\
do {				\
    IF_ROSETTA() {		\
	exprs			\
    }				\
} while(0)

#endif /*  _LIBKERN_OSCROSSENDIAN_H */
