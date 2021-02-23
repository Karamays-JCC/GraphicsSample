#pragma once
#include <objbase.h>
#include <stdio.h>
#include <string>

class UGUIDMaker
{
public:
	static const std::string GenerateGUID()
	{
		static char buf[64] = { 0 };
		GUID guid;
		if (S_OK == ::CoCreateGuid(&guid))
		{
			_snprintf(buf, sizeof(buf)
				, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
				, guid.Data1
				, guid.Data2
				, guid.Data3
				, guid.Data4[0], guid.Data4[1]
				, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
				, guid.Data4[6], guid.Data4[7]
			);
		}
		return std::string(buf);
	}
};

