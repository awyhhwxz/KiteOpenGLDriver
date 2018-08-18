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
		_aabb.Reset();

		for (int vertexI = 0; vertexI < vertexCount; ++vertexI)
		{
			auto verticesPointer = verices + vertexI;
			_vertices.push_back(*verticesPointer);
			_aabb.Extend(*verticesPointer);
		}
	}
	void KiteDriverMesh::SetNormals(kite_math::Vector3f * normals, int normalCount)
	{
		_normals.clear();

		for (int normalI = 0; normalI < normalCount; ++normalI)
		{
			auto normalsPointer = normals + normalI;
			_normals.push_back(*normalsPointer);
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

	float * KiteDriverMesh::GetNormals()
	{
		return (float*)_normals.data();
	}

	float * KiteDriverMesh::GetVertices()
	{
		return (float*)_vertices.data();
	}

	uint16* KiteDriverMesh::GetIndices()
	{
		return _indices.data();
	}

	float * KiteDriverMesh::GetUVs(int uv_index)
	{
		return (float*)_uvs_map[uv_index].data();
	}

	bool KiteDriverMesh::RayCast(kite_math::Ray ray, kite_math::RayCastInfo& raycastinfo)
	{
		if (!_aabb.RayCast(ray))
		{
			return false;
		}

		bool is_cast = false;
		raycastinfo.Distance = kite_math::Mathf::kFloatMaxValue;

		int face_count = _indices.size() / 3;
		auto triangle_data = _indices.data();
		kite_math::Vector3f points[3];
		for (int face_i = 0 ; face_i < face_count ; ++face_i, triangle_data += 3)
		{
			points[0] = _vertices[triangle_data[0]];
			points[1] = _vertices[triangle_data[1]];
			points[2] = _vertices[triangle_data[2]];

			if (RayCastTriangle(ray, points, raycastinfo))
			{
				is_cast = true;
			}
		}

		if (is_cast)
		{
			raycastinfo.Position = kite_math::Triangle::ComputeDataViaBarycentric(points, raycastinfo.BarycentricWeight);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool KiteDriverMesh::RayCastTriangle(kite_math::Ray ray, kite_math::Vector3f points[3], kite_math::RayCastInfo& raycastinfo)
	{
		kite_math::Plane plane(points);
		auto ray_normal_cos = kite_math::Vector3f::Dot(plane.get_normal(), ray.get_direction());
		if (ray_normal_cos < 0)
		{
			float distance = -1;
			if (ray.CastPlane(plane, distance))
			{
				kite_math::Vector3f barycentric_weight;
				kite_math::Vector3f intersection_point = ray.get_origin() + distance * ray.get_direction();
				if (kite_math::Triangle::IsPointInTriangle(points, intersection_point, barycentric_weight))
				{
					if (distance < raycastinfo.Distance)
					{
						raycastinfo.BarycentricWeight = barycentric_weight;
						raycastinfo.Distance = distance;
						return true;
					}
				}
			}
		}

		return false;
	}

}