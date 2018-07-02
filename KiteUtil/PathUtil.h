#pragma once
namespace kite_util
{
	class KITE_UTIL_API PathUtil
	{
	public:
		static std::string GetAppPath();
		static std::string GetFileDirectory(const std::string& fileName);
	};

}