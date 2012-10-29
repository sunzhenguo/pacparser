// pacparser.net.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include "..\..\src\pacparser.h"
#include <stdlib.h>
#include <string.h>
#include <msclr/marshal.h>

#using <mscorlib.dll>

using namespace System;
using namespace msclr::interop;
using System::Runtime::InteropServices::Marshal;


namespace PacParser
{

	/// <summary>
	/// 
	/// </summary>
	public ref class PacParser abstract sealed
	{

		private:


			static marshal_context^ _context;



			static const char* MarshalString(String^ str)
			{				
				return _context->marshal_as<const char*>(str);
			}


		public:


			/// <summary>
			/// 
			/// </summary>
			/// <param name="enableMsExt"></param>
			static Boolean Initialize()
			{
				_context = gcnew marshal_context();				

				return (Boolean)pacparser_init();
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="enableMsExt"></param>
			static Boolean InitializeMS()
			{
				EnableMicrosoftExtensions();

				return Initialize();
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="pacPath"></param>
			static Boolean ParsePacFile(String ^pacPath)
			{
				const char *ansiPath = MarshalString(pacPath);

				return pacparser_parse_pac_file(ansiPath);
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="pacString"></param>
			static Boolean ParsePacString(String ^pacString)
			{
				const char *ansiPac = MarshalString(pacString);

				return pacparser_parse_pac_string(ansiPac);
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <returns></returns>
			static String^ FindProxy(String ^url, String ^host)
			{
				const char *ansiUrl = MarshalString(url);
				const char *ansiHost = MarshalString(host);

				return gcnew String(pacparser_find_proxy(ansiUrl, ansiHost));
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacPath"></param>
			/// <returns></returns>
			static String^ JustFindProxyFromFile(String ^url, String ^host, String^ pacPath)
			{
				const char *ansiUrl = MarshalString(url);
				const char *ansiHost = MarshalString(host);
				const char *ansiPath = MarshalString(pacPath);

				return gcnew String(pacparser_just_find_proxy(ansiUrl, ansiHost, ansiPath));
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacPath"></param>
			/// <returns></returns>
			static String^ JustFindProxyFromFileMS(String ^url, String ^host, String ^pacPath)
			{
				EnableMicrosoftExtensions();

				return JustFindProxyFromFile(url, host, pacPath);
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacString"></param>
			/// <returns></returns>
			static String^ JustFindProxyFromString(String ^url, String ^host, String ^pacString)
			{
				const char *ansiUrl = MarshalString(url);
				const char *ansiHost = MarshalString(host);
				const char *ansiPath = MarshalString(pacString);

				return gcnew String(pacparser_just_find_proxy(ansiUrl, ansiHost, ansiPath));
			}


			
			/// <summary>
			/// 
			/// </summary>
			/// <param name="url"></param>
			/// <param name="host"></param>
			/// <param name="pacString"></param>
			/// <returns></returns>
			static String^ JustFindProxyFromStringMS(String ^url, String ^host, String ^pacString)
			{
				EnableMicrosoftExtensions();

				return JustFindProxyFromString(url, host, pacString);
			}



			/// <summary>
			/// 
			/// </summary>
			static void EnableMicrosoftExtensions()
			{
				pacparser_enable_microsoft_extensions();
			}



			/// <summary>
			/// 
			/// </summary>
			/// <param name="ip"></param>
			static void SetIP(String ^ip)
			{
				const char *ansiIp = MarshalString(ip);

				pacparser_setmyip(ansiIp);
			}



			/// <summary>
			/// 
			/// </summary>
			static void Cleanup()
			{
				pacparser_cleanup();

				delete _context;
			}



			/// <summary>
			/// 
			/// </summary>
			static property String ^PacParserVersion
			{
				String^ get()
				{
					return gcnew String(pacparser_version());
				}
			}
	};
};