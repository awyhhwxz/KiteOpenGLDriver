#pragma once
namespace kite_fbx
{
	struct KITE_FBX_API FbxMeshData
	{
		std::vector<kite_math::Vector3f> Vertices;
		std::map<int, std::vector<kite_math::Vector3f>> Normals;
		std::map<int, std::vector<kite_math::Vector2f>> UVs;
		int Count;

		void Append(FbxMeshData* data);
		void Clear();
		void ResetCount();
	};

}