#pragma once

namespace kite_fbx
{
	class IFbxMesh
	{
	public:
		virtual const FbxMeshData& get_mesh_data() = 0;
		virtual const std::vector<unsigned short>& get_indexes() = 0;

	};

	typedef std::shared_ptr<IFbxMesh> IFbxMeshPtr;
}