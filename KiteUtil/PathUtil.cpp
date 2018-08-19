#include "stdafx.h"
#include "PathUtil.h"
#include <windows.h>
#include <math.h>

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

	tstring PathUtil::GetFileDirectory(const tchar* file_path)
	{
		tstring result(file_path);
		auto flash_index = IndexLastFlash(result);
		return result.substr(0, flash_index);
	}

	void PathUtil::SplitDirectoryAndFileName(const tchar* file_path, tstring& directory, tstring& file_name)
	{
		tstring result(file_path);
		auto flash_index = IndexLastFlash(result);
		directory = result.substr(0, flash_index + 1);
		file_name = result.substr(flash_index + 1);
	}

	tstring PathUtil::AddDirectoryFlash(const tchar * directory)
	{
		tstring result(directory);
		if (result.begin() != result.end())
		{
			const tchar& last_char = *result.rbegin();
			if (last_char != '/' && last_char != '\\')
			{
				result += '/';
			}
		}
		return result;
	}

	int PathUtil::IndexLastFlash(const tstring& str)
	{
		auto begin_iter = str.rbegin();
		auto end_iter = str.rend();
		int index = -1;
		while (begin_iter != end_iter)
		{
			const auto& c = *begin_iter;
			if (c == '/' || c == '\\')
			{
				index = (str.size() - 1) - (begin_iter - str.rbegin());
				break;
			}

			++begin_iter;
		}

		return index;
	}

}