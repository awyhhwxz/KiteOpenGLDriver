#include "stdafx.h"
#include "KiteDriverGeometryGenerator.h"

using namespace kite_math;

namespace kite_driver
{
	KiteDriverMeshPtr KiteDriverGeometryGenerator::Cuboid(float x_length, float y_length, float z_length)
	{
		std::shared_ptr<KiteDriverMesh> mesh = std::make_shared<KiteDriverMesh>();

		auto vertices = CuboidVertices(x_length, y_length, z_length);
		mesh->SetVertices(vertices.get(), 8);
		
		Vector2f uv0[] = {
			Vector2f(0, 0),
			Vector2f(1, 0),
			Vector2f(0, 1),
			Vector2f(1, 1),
			Vector2f(1, 1),
			Vector2f(0, 1),
			Vector2f(1, 0),
			Vector2f(0, 0),
		};
		mesh->SetUVs(0, uv0, 8);

		GLushort indexes[] = {
			0, 1, 2,  //up
			1, 3, 2,
			4, 6, 5,  //bottom
			5, 6, 7,
			1, 5, 3,  //left
			5, 7, 3,
			0, 2, 6,  //right
			4, 0, 6,
			1, 0, 5,  //front
			5, 0, 4,
			2, 3, 7,  //back
			2, 7, 6,
		};
		mesh->SetIndices(indexes, 3 * 12);
		return mesh;
	}

	kite_driver::KiteDriverMeshPtr KiteDriverGeometryGenerator::Plane(float x_length, float y_length)
	{
		std::shared_ptr<KiteDriverMesh> mesh = std::make_shared<KiteDriverMesh>();

		auto x_half_length = x_length * 0.5f;
		auto y_half_length = y_length * 0.5f;

		Vector3f vertices[] = {
			Vector3f(x_length, y_length, 0),
			Vector3f(x_length, -y_length, 0),
			Vector3f(-x_length, y_length, 0),
			Vector3f(-x_length, -y_length, 0),
		};
		mesh->SetVertices(vertices, 4);

		Vector2f uv0[] = {
			Vector2f(1, 1),
			Vector2f(1, 0),
			Vector2f(0, 1),
			Vector2f(0, 0),
		};
		mesh->SetUVs(0, uv0, 4);

		GLushort indexes[] = {
			0, 2, 1,
			2, 3, 1
		};
		mesh->SetIndices(indexes, 3 * 2);

		return mesh;
	}

	kite_driver::KiteDriverMeshPtr KiteDriverGeometryGenerator::SkyBoxMesh()
	{

		std::shared_ptr<KiteDriverMesh> mesh = std::make_shared<KiteDriverMesh>();


		auto vertices = CuboidVertices(2.0, 2.0, 2.0);
		mesh->SetVertices(vertices.get(), 8);

		GLushort indexes[] = {
			0, 2, 1,  //up
			1, 2, 3,
			4, 5, 6,  //bottom
			5, 7, 6,
			1, 3, 5,  //left
			5, 3, 7,
			0, 6, 2,  //right
			4, 6, 0,
			1, 5, 0,  //front
			5, 4, 0,
			2, 7, 3,  //back
			2, 6, 7,
		};
		mesh->SetIndices(indexes, 3 * 12);
		return mesh;
	}

	std::unique_ptr<kite_math::Vector3f[]> KiteDriverGeometryGenerator::CuboidVertices(float x_length, float y_length, float z_length)
	{
		auto x_half_length = x_length * 0.5f;
		auto y_half_length = y_length * 0.5f;
		auto z_half_length = z_length * 0.5f;

		std::unique_ptr<kite_math::Vector3f[]> vertices;
		
		vertices.reset(
			new Vector3f[8]{
				Vector3f(x_half_length, y_half_length, z_half_length),
				Vector3f(x_half_length, y_half_length, -z_half_length),
				Vector3f(-x_half_length, y_half_length, z_half_length),
				Vector3f(-x_half_length, y_half_length, -z_half_length),
				Vector3f(x_half_length, -y_half_length, z_half_length),
				Vector3f(x_half_length, -y_half_length, -z_half_length),
				Vector3f(-x_half_length, -y_half_length, z_half_length),
				Vector3f(-x_half_length, -y_half_length, -z_half_length),
			}
		);
		
		return vertices;
	}

}