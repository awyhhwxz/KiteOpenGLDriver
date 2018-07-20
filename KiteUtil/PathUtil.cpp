#include "stdafx.h"
#include "PathUtil.h"
#include <windows.h>

namespace kite_util
{

	tstring PathUtil::GetAppPath()
	{
		char fullPath[MAX_PATH];
		GetModuleFileNameA(NULL, fullPath, MAX_PATH);
		return GetFileDirectory(fullPath);
	}

	tstring PathUtil::GetResourcePath()
	{
		return GetAppPath() + "/resources";
	}

	tstring PathUtil::GetFileDirectory(const tstring& fileName)
	{
		auto index = fileName.find_last_of('\\');
		return fileName.substr(0, index);
	}

}