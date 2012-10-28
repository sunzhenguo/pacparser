// pacparser.net.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "..\..\src\pacparser.h"
#include "AutoPtr.h"

#using <mscorlib.dll>

#pragma managed

using namespace System;
using System::Runtime::InteropServices::Marshal;

namespace PacParser{

public ref class PacParser abstract
{


public:


	static bool Initialize()
	{
		return Initialize(false);
	}

	static bool Initialize(bool enableMsExt)
	{
		if(enableMsExt)
		{
			EnableMicrosoftExtensions();
		}

		return (bool)pacparser_init();
	}


	static bool ParsePacFile(String ^pacPath)
	{
		AutoPtr<char> ansiPath = (char*)(void*)Marshal::StringToHGlobalAnsi(pacPath);

		return (bool)pacparser_parse_pac_file(ansiPath);
	}

	static bool ParsePacString(String ^pacString)
	{
		const char *ansiPac = (char*)(void*)Marshal::StringToHGlobalAnsi(pacString);

		return (bool)pacparser_parse_pac_file(ansiPac);
	}

	static String^ FindProxy(String ^url, String ^host)
	{
		const char *ansiUrl = (char*)(void*)Marshal::StringToHGlobalAnsi(url);
		const char *ansiHost = (char*)(void*)Marshal::StringToHGlobalAnsi(host);

		return gcnew String(pacparser_find_proxy(ansiUrl, ansiHost));
	}

	static String^ FindProxyFromFile(String ^url, String ^host, String^ pacPath)
	{
		const char *ansiUrl = (char*)(void*)Marshal::StringToHGlobalAnsi(url);
		const char *ansiHost = (char*)(void*)Marshal::StringToHGlobalAnsi(host);
		const char *ansiPath = (char*)(void*)Marshal::StringToHGlobalAnsi(pacPath);

		return gcnew String(pacparser_just_find_proxy(ansiUrl, ansiHost, ansiPath));
	}

	static String^ FindProxyFromFileMS(String ^url, String ^host, String^ pacPath)
	{
		EnableMicrosoftExtensions();
		return FindProxyFromFile(url, host, pacPath);
	}

	static String^ FindProxyFromString(String ^url, String ^host, String^ pacString)
	{
		const char *ansiUrl = (char*)(void*)Marshal::StringToHGlobalAnsi(url);
		const char *ansiHost = (char*)(void*)Marshal::StringToHGlobalAnsi(host);
		const char *ansiPath = (char*)(void*)Marshal::StringToHGlobalAnsi(pacString);

		return gcnew String(pacparser_just_find_proxy(ansiUrl, ansiHost, ansiPath));
	}

		static String^ FindProxyFromStringMS(String ^url, String ^host, String^ pacString)
	{
		EnableMicrosoftExtensions();
		return FindProxyFromString(url, host, pacString);
	}


	static void EnableMicrosoftExtensions()
	{
		pacparser_enable_microsoft_extensions();
	}

	static void SetIP(String ^ip)
	{
		const char *ansiIp = (char*)(void*)Marshal::StringToHGlobalAnsi(ip);
		pacparser_setmyip(ansiIp);
	}

	static property String ^PacParserVersion
	{
		String^ get()
		{
			return gcnew String(pacparser_version());
		}
	}
};
};