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


#include "stdafx.h"
#include "marshalled_cstring.h"
#include "pacparser.h"
#include <stdlib.h>
#include <string.h>
#include <msclr/marshal.h>

#using <mscorlib.dll>

using namespace System;
using namespace System::Net;
using namespace msclr::interop;

using System::Runtime::InteropServices::Marshal;



namespace PacParserDotNet
{

	delegate Boolean ParsePacTarget(String ^target);

	/// <summary>
	/// Defacto static class that wraps calls to the pacparser library
	/// and extends it with a few convenience methods.
	/// </summary>
	public ref class PacParser abstract sealed
	{

		private:

			/// <summary>
			/// Allows invoker to provide parsing logic to _FindProxyFromTarget.  Readonly.
			/// </summary>
			static initonly ParsePacTarget ^_parseStringDelegate = gcnew ParsePacTarget(ParsePacString);
			

			/// <summary>
			/// Allows invoker to provide parsing logic to _FindProxyFromTarget.  Readonly.
			/// </summary>
			static initonly ParsePacTarget ^_parseFileDelegate = gcnew ParsePacTarget(ParsePacFile);


			/// <summary>
			/// This function is a wrapper around pacparser_parse_pac_string, pacparser_find_proxy
			/// and pacparser_cleanup. If you just want to find out proxy a given set of pac file,
			/// url and host, this is the function to call. This function takes care of all the
			/// initialization and cleanup.
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacString"></param>
			/// <returns></returns>
			static String^ _FindProxyFromTarget(String ^url, String ^host, String ^pacTarget, ParsePacTarget ^parseFunc)
			{
				String ^proxy = nullptr;

				// call the delegate that will parse the pac file
				if(parseFunc(pacTarget))
				{
					proxy = FindProxy(url, host);
					if(proxy == nullptr)
					{
						proxy = "";
					}
				}

				Cleanup();

				return proxy;
			}


			/// <summary>
			/// Encapsulates char* marshalling.  May end up being pointless, but nice to have one place to make changes.
			/// </summary>
			static String^ _MarshalToMngd(char* str)
			{
				return gcnew String(str);
			}


		public:


			/// <summary>
			/// Initializes JavaScript engine and does few
			/// basic initializations specific to pacparser.
			/// </summary>
			/// <returns>True on success.</returns>
			static Boolean Initialize()
			{
				return pacparser_init();
			}


			/// <summary>
			/// Initializes JavaScript engine, Microsoft extensions, and
			/// does few basic initializations specific to pacparser.
			/// </summary>
			/// <returns>True on success.</returns>
			static Boolean InitializeMS()
			{
				EnableMicrosoftExtensions();

				return Initialize();
			}


			/// <summary>
			/// This function should be called once you're done with using pacparser engine.
			/// </summary>
			static void Cleanup()
			{
				try
				{
					pacparser_cleanup();
				}
				catch(AccessViolationException ^ex)
				{		
					using namespace System::Diagnostics;
					Trace::WriteLine(ex->StackTrace);
				}
			}
			

			/// <summary>
			/// Enables a subset of Microsoft PAC extensions - dnsResolveEx, myIpAddressEx,
			/// isResolvableEx. These functions are used by Google Chrome and IE to work
			/// with IPv6. More info: http://code.google.com/p/pacparser/issues/detail?id=4
			/// </summary>
			static void EnableMicrosoftExtensions()
			{
				pacparser_enable_microsoft_extensions();
			}


			/// <summary>
			/// Sets IP address to a custom value.  Otherwise, pacparsers uses its default logic
			/// to get the host's IP.  The IP address is that returned by the myIpAddress()
			/// javascript function.
			/// </summary>
			/// <param name="ip"></param>
			static void SetIP(String ^ip)
			{
				MarshalledCString ^ansiIp = gcnew MarshalledCString(ip);

				pacparser_setmyip(ansiIp->ToAnsi());
			}


			/// <summary>
			/// Sets IP address to a custom value. This is the IP address returned by
			/// myIpAddress() javascript function.
			/// </summary>
			/// <param name="ip"></param>
			static void SetIP(IPAddress ^ip)
			{
				SetIP(ip->ToString());
			}


			/// <summary>
			/// Reads a PAC file and evaluates it in the
			/// JavaScript context created by pacparser_init
			/// </summary>
			/// <param name="pacPath"></param>
			static Boolean ParsePacFile(String ^pacPath)
			{
				MarshalledCString ^ansiPath = gcnew MarshalledCString(pacPath);

				return pacparser_parse_pac_file(ansiPath->ToAnsi());
			}


			/// <summary>
			/// Reads a PAC string and evaluates it in the
			/// JavaScript context created by pacparser_init 
			/// </summary>
			/// <param name="pacString"></param>
			static Boolean ParsePacString(String ^pacString)
			{
				MarshalledCString ^ansiPac = gcnew MarshalledCString(pacString);

				return pacparser_parse_pac_string(ansiPac->ToAnsi());
			}


			/// <summary>
			/// Finds proxy for the given URL and Host. This function should be called only
			/// after pacparser engine has been initialized (using pacparser_init) and pac
			/// script has been parsed (using pacparser_parse_pac_file or
			/// pacparser_parse_pac_string).
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <returns>Proxy string on sucess and NULL on error.</returns>
			static String^ FindProxy(String ^url, String ^host)
			{
				MarshalledCString ^ansiUrl = gcnew MarshalledCString(url);
				MarshalledCString ^ansiHost = gcnew MarshalledCString(host);

				return _MarshalToMngd(pacparser_find_proxy(ansiUrl->ToAnsi(), ansiHost->ToAnsi()));
			}


			/// <summary>
			/// This function is a wrapper around functions pacparser_init,
			/// pacparser_parse_pac_file, pacparser_find_proxy and pacparser_cleanup. If
			/// you just want to find out proxy a given set of pac file, url and host, this
			/// is the function to call. This function takes care of all the initialization
			/// and cleanup.
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacPath"></param>
			/// <returns>Proxy string on sucess and NULL on error.</returns>
			static String^ JustFindProxyFromFile(String ^url, String ^host, String^ pacPath)
			{
				Initialize();

				return _FindProxyFromTarget(url, host, pacPath, _parseFileDelegate);
			}


			/// <summary>
			/// This function is a wrapper around functions pacparser_enable_microsoft_extensions,
			/// pacparser_init, pacparser_parse_pac_file, pacparser_find_proxy and pacparser_cleanup. If
			/// you just want to find out proxy a given set of pac file, url and host, this is the
			/// function to call. This function takes care of all the initialization and cleanup.
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacPath"></param>
			/// <returns>Proxy string on sucess and NULL on error.</returns>
			static String^ JustFindProxyFromFileMS(String ^url, String ^host, String ^pacPath)
			{
				InitializeMS();

				return _FindProxyFromTarget(url, host, pacPath, _parseFileDelegate);
			}


			/// <summary>
			/// This function is a wrapper around functions pacparser_enable_microsoft_extensions,
			/// pacparser_init, pacparser_parse_pac_string, pacparser_find_proxy and pacparser_cleanup. If
			/// you just want to find out proxy a given set of pac file, url and host, this is the
			/// function to call. This function takes care of all the initialization and cleanup.
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacString"></param>
			/// <returns>Proxy string on sucess and NULL on error.</returns>
			static String^ JustFindProxyFromStringMS(String ^url, String ^host, String ^pacString)
			{
				InitializeMS();

				return _FindProxyFromTarget(url, host, pacString, _parseStringDelegate);
			}

			
			/// <summary>
			/// This function is a wrapper around functions pacparser_init,
			/// pacparser_parse_pac_string, pacparser_find_proxy and pacparser_cleanup. If
			/// you just want to find out proxy a given set of pac file, url and host, this
			/// is the function to call. This function takes care of all the initialization
			/// and cleanup.
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacString"></param>
			/// <returns></returns>
			static String^ JustFindProxyFromString(String ^url, String ^host, String ^pacString)
			{
				Initialize();

				return _FindProxyFromTarget(url, host, pacString, _parseStringDelegate);
			}


			/// <summary>
			/// Version string is determined at the time of build. If built from a released
			/// package, version corresponds to the latest release (hg) tag. If built from the
			/// repository, it corresponds to the head revision of the repo.
			/// </summary>
			/// <returns>Version string if defined, "" otherwise.</returns>
			static property String^ Version
			{
				String^ get()
				{
					return _MarshalToMngd(pacparser_version());
				}
			}
	};
};