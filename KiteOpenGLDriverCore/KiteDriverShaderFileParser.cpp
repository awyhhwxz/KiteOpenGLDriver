#include "stdafx.h"
#include "KiteDriverShaderFileParser.h"
#include <fstream>
#include <regex>

namespace kite_driver
{
	KiteDriverShaderFileParser::KiteDriverShaderFileParser()
	{
	}


	KiteDriverShaderFileParser::~KiteDriverShaderFileParser()
	{
	}

	tstring KiteDriverShaderFileParser::ReadShaderString(const tchar* file_path)
	{
		tstring dircectory, file_name;
		kite_util::PathUtil::SplitDirectoryAndFileName(file_path, dircectory, file_name);

		std::vector<std::string> included_files;
		return ReadShaderStringInner(dircectory.c_str(), file_name.c_str(), included_files);
	}

	tstring KiteDriverShaderFileParser::ReadShaderStringInner(const tchar * directory, const tchar * filename, std::vector<std::string> included_files)
	{
		if (std::find(included_files.begin(), included_files.end(), filename) != included_files.end()) return "";
		included_files.push_back(filename);

		tstring file_path;
		file_path = file_path + directory + filename;
		std::ifstream ifs(file_path.c_str());
		std::string read, result, include_path;

		if (ifs)
		{
			while (std::getline(ifs, read))
			{
				if (TryInclude(read.c_str(), include_path))
				{
					if (std::find(included_files.begin(), included_files.end(), include_path) == included_files.end())
					{
						read = ReadShaderStringInner(directory, include_path.c_str(), included_files);
					}
					else
					{
						read = "";
					}
				}
				result += read + "\r\n";
			}

			ifs.close();
		}

		return result;
	}

	bool KiteDriverShaderFileParser::TryInclude(const tchar * content, tstring& includefilepath)
	{
		auto e = std::regex("#include *\"([a-zA-Z0-9_]+\.[a-zA-Z0-9_]+)\"");
		std::smatch matched;
		tstring s(content);
		if (regex_search(s, matched, e))
		{
			includefilepath = matched[1];
			return true;
		}
		else
		{
			return false;
		}
	}
}