#include "stdafx.h"
#include "StringReader.h"
#include <fstream>

namespace kite_util
{

	std::string kite_util::StringReader::ReadString(const char* filePath)
	{
		std::ifstream ifs(filePath);
		std::string read, result;

		if (ifs)
		{
			while (std::getline(ifs, read))
			{
				result += read + "\r\n";
			}

			ifs.close();
		}

		return result;
	}

}