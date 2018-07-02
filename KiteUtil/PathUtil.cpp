#include "stdafx.h"
#include "PathUtil.h"
#include <windows.h>

namespace kite_util
{

	std::string PathUtil::GetAppPath()
	{
		char fullPath[MAX_PATH];
		GetModuleFileNameA(NULL, fullPath, MAX_PATH);
		return GetFileDirectory(fullPath);
	}

	std::string PathUtil::GetFileDirectory(const std::string& fileName)
	{
		auto index = fileName.find_last_of('\\');
		return fileName.substr(0, index);
	}

}