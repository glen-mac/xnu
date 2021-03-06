/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1998 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 * 23 Nov 98 sdouglas created from objc version.
 */
 
#include <IOKit/system.h>

#include <IOKit/pci/IOPCIBridge.h>
#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/IOLib.h>
#include <IOKit/assert.h>

#include <libkern/c++/OSContainers.h>

#include <architecture/i386/pio.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

UInt32 IOPCIDevice::ioRead32( UInt16 offset, IOMemoryMap * map = 0 )
{
    UInt32	value;

    if( 0 == map)
	map = ioMap;

    value = inl( map->getPhysicalAddress() + offset );

    return( value );
}

UInt16 IOPCIDevice::ioRead16( UInt16 offset, IOMemoryMap * map = 0 )
{
    UInt16	value;

    if( 0 == map)
	map = ioMap;

    value = inw( map->getPhysicalAddress() + offset );

    return( value );
}

UInt8 IOPCIDevice::ioRead8( UInt16 offset, IOMemoryMap * map = 0 )
{
    UInt32	value;

    if( 0 == map)
	map = ioMap;

    value = inb( map->getPhysicalAddress() + offset );

    return( value );
}

void IOPCIDevice::ioWrite32( UInt16 offset, UInt32 value,
				IOMemoryMap * map = 0 )
{
    if( 0 == map)
	map = ioMap;

    outl( map->getPhysicalAddress() + offset, value );
}

void IOPCIDevice::ioWrite16( UInt16 offset, UInt16 value,
				IOMemoryMap * map = 0 )
{
    if( 0 == map)
	map = ioMap;

    outw( map->getPhysicalAddress() + offset, value );
}

void IOPCIDevice::ioWrite8( UInt16 offset, UInt8 value,
				IOMemoryMap * map = 0 )
{
    if( 0 == map)
	map = ioMap;

    outb( map->getPhysicalAddress() + offset, value );
}

