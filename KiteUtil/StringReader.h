#pragma once

#include "kite_driver_typedef.h"
namespace kite_util
{
	class KITE_UTIL_API StringReader
	{
	public: 
		static std::string ReadString(const char* filePath);
	};
}

