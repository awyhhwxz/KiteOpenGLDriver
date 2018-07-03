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

	float * KiteDriverMesh::GetVertices()
	{
		return (float*)&_vertices[0];
	}

	uint16* KiteDriverMesh::GetIndices()
	{
		return &_indices[0];
	}

}