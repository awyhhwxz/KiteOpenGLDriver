#pragma once

namespace kite_driver
{
	class KiteDriverGeometryGenerator
	{
	public:

		static KiteDriverMeshPtr Cuboid(float x_length, float y_length, float z_length);
		static KiteDriverMeshPtr Plane(float x_length, float y_length);
		static KiteDriverMeshPtr SkyBoxMesh();

	private:
		static std::unique_ptr<kite_math::Vector3f[]> CuboidVertices(float x_length, float y_length, float z_length);
	};
}

