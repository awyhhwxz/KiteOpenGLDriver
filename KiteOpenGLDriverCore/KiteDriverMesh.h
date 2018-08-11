#pragma once


namespace kite_driver
{
	class KiteDriverMesh
	{
	public:
		KiteDriverMesh();
		~KiteDriverMesh();

		void SetVertices(kite_math::Vector3f* verices, int vertexCount);
		void SetIndices(uint16 * indices, int indexCount);
		void SetUVs(int uv_index, kite_math::Vector2f* uvs, int vertexCount);

		float* GetVertices();
		inline int GetVertexCount() { return _vertices.size(); }

		uint16* GetIndices();
		inline int GetIndexCount() { return _indices.size(); }

		float* GetUVs(int uv_index);
		inline int GetUVChannelCount() { return _uvs_map.size(); }

		bool RayCast(kite_math::Ray ray, kite_math::RayCastInfo& raycastinfo);

	protected:
		bool RayCastTriangle(kite_math::Ray ray, kite_math::Vector3f points[3], kite_math::RayCastInfo& raycastinfo);

	private:
		std::vector<kite_math::Vector3f> _vertices;
		std::vector<uint16> _indices;
		std::map<int, std::vector<kite_math::Vector2f>> _uvs_map;
		KiteDriverAABB _aabb;
	};

	typedef std::shared_ptr<KiteDriverMesh> KiteDriverMeshPtr;
}