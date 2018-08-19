#pragma once

#include "kite_driver_typedef.h"
namespace kite_util
{
	class KITE_UTIL_API PathUtil
	{
	public:
		static tstring GetAppPath();
		static tstring GetResourcePath();
		static tstring GetFileDirectory(const tchar* file_path);
		static void SplitDirectoryAndFileName(const tchar* file_path, tstring& directory, tstring& file_name);
		static tstring AddDirectoryFlash(const tchar* directory);

	private:
		static int IndexLastFlash(const tstring& str);
	};

}