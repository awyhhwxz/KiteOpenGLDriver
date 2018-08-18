#include "stdafx.h"
#include "KiteDriverFbxVisitor.h"

namespace kite_driver
{
	KiteDriverFbxVisitor::KiteDriverFbxVisitor()
	{
	}


	KiteDriverFbxVisitor::~KiteDriverFbxVisitor()
	{
	}

	void KiteDriverFbxVisitor::LoadFbx(const tchar* fbx_path)
	{
		kite_fbx::FbxParser fbx_parser;
		auto node_parser = fbx_parser.LoadFbx(fbx_path);

		_meshes.clear();
		auto meshes = node_parser->get_meshes();
		std::for_each(meshes.begin(), meshes.end(), [this](const auto& mesh)
		{
			_meshes.push_back(ParseFbxMesh(mesh.get()));
		});
	}

	KiteDriverMeshPtr KiteDriverFbxVisitor::ParseFbxMesh(kite_fbx::IFbxMesh* fbx_mesh)
	{
		KiteDriverMeshPtr mesh = std::make_shared<KiteDriverMesh>();
		
	    const auto& fbx_mesh_data = fbx_mesh->get_mesh_data();
		mesh->SetVertices(const_cast<kite_math::Vector3f*>(fbx_mesh_data.Vertices.data()), fbx_mesh_data.Vertices.size());
		const auto& fbx_mesh_uvs = fbx_mesh_data.UVs;
		std::for_each(fbx_mesh_uvs.begin(), fbx_mesh_uvs.end(), [&mesh](const auto& uv_pair)
		{
			mesh->SetUVs(uv_pair.first, const_cast<kite_math::Vector2f*>(uv_pair.second.data()), uv_pair.second.size());
		});

		const auto& fbx_normals = fbx_mesh_data.Normals;
		if (fbx_normals.size() != 0)
		{
			const auto& normal = (*fbx_normals.begin()).second;
			mesh->SetNormals(const_cast<kite_math::Vector3f*>(normal.data()), normal.size());
		}

		const auto& indices = fbx_mesh->get_indexes();
		mesh->SetIndices(const_cast<uint16*>(indices.data()), indices.size());
		return mesh;
	}

}