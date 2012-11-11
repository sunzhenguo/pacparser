// Copyright (C) 2012 Eric Millin.
// Author: Eric Millin <etmillin@gmail.com>
//
// This file defines the MarshalledString class for pacparserdotnet.
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

#include "stdafx.h"
#include "marshalledstring.h"
#include <stdlib.h>
#include <string.h>
#include <msclr/marshal.h>

#using <mscorlib.dll>

using namespace System;

using System::Runtime::InteropServices::Marshal;


namespace PacParserDotNet
{

	MarshalledString::MarshalledString(String ^str)
		: _cString(Marshal::StringToHGlobalAnsi(str))
	{		
	}			


	MarshalledString::~MarshalledString()
	{
		Marshal::FreeHGlobal(this->_cString);
	}


	const char* MarshalledString::ToAnsi()
	{
		return static_cast<const char*>(this->_cString.ToPointer());
	}

};
