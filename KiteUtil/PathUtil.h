#pragma once

#include "kite_driver_typedef.h"
namespace kite_util
{
	class KITE_UTIL_API PathUtil
	{
	public:
		static tstring GetAppPath();
		static tstring GetResourcePath();
		static tstring GetFileDirectory(const tstring& fileName);
	};

}