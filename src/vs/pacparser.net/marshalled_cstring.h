// Copyright (C) 2012 Eric Millin.
// Author: Eric Millin <etmillin@gmail.com>
//
// This file defines the MarshalledCString class for pacparserdotnet.
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

using namespace System;

namespace PacParserDotNet
{

	/// <summary>
	/// Simple .NET-style RAII wrapper for C-style char* strings.
	/// </summary>
	ref class MarshalledCString
	{

		private:

			// .NET pointer for string storage
			IntPtr _cString;

			// disposed flag
			bool _disposed;

		public:

			// Ctor
			MarshalledCString(String ^str);	


			// Destructor for deterministic cleanup.
			~MarshalledCString();


			// Finalizer called deterministically by destructor and non-deterministically by GC.
			!MarshalledCString();


			// Returns a C-style ANSI string.
			const char* ToAnsi();

	};
};