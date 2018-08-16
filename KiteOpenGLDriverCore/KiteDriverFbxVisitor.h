#pragma once

#include "FbxParserPluginLib.h"

namespace kite_driver
{
	class KiteDriverFbxVisitor
	{
	public:
		KiteDriverFbxVisitor();
		~KiteDriverFbxVisitor();

		void LoadFbx(const tchar* fbx_path);
		KiteDriverMeshPtr FirstMesh() { return *_meshes.begin(); }
	private:
		KiteDriverMeshPtr ParseFbxMesh(kite_fbx::IFbxMesh* fbx_mesh);
		std::vector<KiteDriverMeshPtr> _meshes;
	};

}