#pragma once

namespace kite_fbx
{
	class KITE_FBX_API FbxParser
	{
	public:
		FbxParser();
		~FbxParser();

		IFbxNodePtr LoadFbx(const char* fbx_path);
	};

}
