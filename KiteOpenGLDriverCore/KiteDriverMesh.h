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

		float* GetVertices();
		inline int GetVertexCount() { return _vertices.size(); }

		uint16* GetIndices();
		inline int GetIndexCount() { return _indices.size(); }
	private:
		std::vector<kite_math::Vector3f> _vertices;
		std::vector<uint16> _indices;
	};

	typedef std::shared_ptr<KiteDriverMesh> KiteDriverMeshPtr;
}