#include "stdafx.h"
#include "KiteDriverMesh.h"


namespace kite_driver
{
	KiteDriverMesh::KiteDriverMesh()
	{
	}


	KiteDriverMesh::~KiteDriverMesh()
	{
	}

	void KiteDriverMesh::SetVertices(kite_math::Vector3f* verices, int vertexCount)
	{
		_vertices.clear();
		for (int vertexI = 0; vertexI < vertexCount; ++vertexI)
		{
			auto verticesPointer = verices + vertexI;
			_vertices.push_back(*verticesPointer);
		}
	}
	void KiteDriverMesh::SetIndices(uint16* indices, int indexCount)
	{
		_indices.clear();
		for (int indexI = 0; indexI < indexCount; ++indexI)
		{
			auto indicesPointer = indices + indexI;
			_indices.push_back(*indicesPointer);
		}
	}

	void KiteDriverMesh::SetUVs(int uv_index, kite_math::Vector2f * uvs, int vertexCount)
	{
		auto& uvs_cache = _uvs_map[uv_index];
		uvs_cache.clear();
		for (int uvI = 0; uvI < vertexCount; ++uvI)
		{
			auto uvsPointer = uvs + uvI;
			uvs_cache.push_back(*uvsPointer);
		}
	}

	float * KiteDriverMesh::GetVertices()
	{
		return (float*)&_vertices[0];
	}

	uint16* KiteDriverMesh::GetIndices()
	{
		return &_indices[0];
	}

	float * KiteDriverMesh::GetUVs(int uv_index)
	{
		return (float*)&_uvs_map[uv_index][0];
	}

}