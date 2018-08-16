#include "stdafx.h"
#include "FbxMeshData.h"

namespace kite_fbx
{

	void FbxMeshData::Append(FbxMeshData* data)
	{
		Vertices.insert(Vertices.end(), data->Vertices.begin(), data->Vertices.end());
		
		auto& data_normals = data->Normals;
		std::for_each(data_normals.begin(), data_normals.end(), [this](auto& normal_pair)
		{
			auto key = normal_pair.first;
			auto& val = normal_pair.second;
			auto& this_normal = Normals[key];
			this_normal.insert(this_normal.end(), val.begin(), val.end());
		});

		auto& data_uvs = data->UVs;
		std::for_each(data_uvs.begin(), data_uvs.end(), [this](auto& uv_pair)
		{
			auto key = uv_pair.first;
			auto& val = uv_pair.second;
			auto& this_uv = UVs[key];
			this_uv.insert(this_uv.end(), val.begin(), val.end());
		});
	}

	void FbxMeshData::Clear()
	{
		Vertices.clear();
		Normals.clear();
		UVs.clear();
	}

	void FbxMeshData::ResetCount()
	{
		Count = Vertices.size();
	}

}