#pragma once

namespace kite_fbx
{
	class IFbxNode
	{
	public:

		virtual const std::vector<IFbxMeshPtr>& get_meshes() = 0;

	};

	typedef std::shared_ptr<IFbxNode> IFbxNodePtr;
}