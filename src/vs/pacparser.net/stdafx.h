// Copyright (C) 2012 Eric Millin.
// Author: Eric Millin <etmillin@gmail.com>
//
// This file defines the PacParser class for pacparserdotnet.
//
// pacparserdotnet is a library that wraps the pacparser library.  pacparser
// provides methods to parse proxy auto-config (PAC) files. Please read README
// file included with this package for more information about this library.
//
// pacparserdotnet is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.

// pacparserdotnet is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA


#pragma once

// Set minimum version to Windows XP SP3
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif

#ifndef NTDDI_VERSION            
#define NTDDI_VERSION NTDDI_WINXPSP3
#endif

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files:
#include <windows.h>