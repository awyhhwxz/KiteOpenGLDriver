#include "stdafx.h"
#include "KiteDriverGeometryGenerator.h"

using namespace kite_math;

namespace kite_driver
{
	KiteDriverMeshPtr KiteDriverGeometryGenerator::Cuboid(float x_length, float y_length, float z_length)
	{
		auto x_half_length = x_length * 0.5f;
		auto y_half_length = y_length * 0.5f;
		auto z_half_length = z_length * 0.5f;


		std::shared_ptr<KiteDriverMesh> mesh = std::make_shared<KiteDriverMesh>();

		Vector3f v[] = {
			Vector3f(x_half_length, y_half_length, z_half_length),
			Vector3f(x_half_length, y_half_length, -z_half_length),
			Vector3f(-x_half_length, y_half_length, z_half_length),
			Vector3f(-x_half_length, y_half_length, -z_half_length),
			Vector3f(x_half_length, -y_half_length, z_half_length),
			Vector3f(x_half_length, -y_half_length, -z_half_length),
			Vector3f(-x_half_length, -y_half_length, z_half_length),
			Vector3f(-x_half_length, -y_half_length, -z_half_length),
		};
		mesh->SetVertices(v, 8);

		GLushort indexes[] = {
			0, 1, 2, //up
			1, 3, 2,
			4, 6, 5, //bottom
			5, 6, 7,
			1, 5, 3, //left
			5, 7, 3,
			0, 2, 6, //right
			4, 0, 6,
			1, 0, 5, //front
			5, 0, 4,
			2, 3, 7, //back
			2, 7, 6,
		};
		mesh->SetIndices(indexes, 3 * 12);
		return mesh;
	}
}