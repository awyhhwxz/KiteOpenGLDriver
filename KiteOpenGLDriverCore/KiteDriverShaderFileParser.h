#pragma once

namespace kite_driver
{
	class KiteDriverShaderFileParser
	{
	public:
		KiteDriverShaderFileParser();
		~KiteDriverShaderFileParser();

	public:
		static tstring ReadShaderString(const tchar* file_path);

	private:
		static tstring ReadShaderStringInner(const tchar* directory, const tchar* filename, std::vector<tstring> included_files);
		static bool TryInclude(const tchar* content, tstring& includefilepath);
	};

}