#include "stdafx.h"
#include "KiteDriverRenderObject.h"

namespace kite_driver
{
	KiteDriverRenderObject::KiteDriverRenderObject()
		: KiteDriverDummy()
	{
		_meshDrawer = std::make_shared<KiteDriverMeshDrawer>();
	}


	KiteDriverRenderObject::~KiteDriverRenderObject()
	{
	}

	kite_driver::KiteDriverObjectType KiteDriverRenderObject::get_type()
	{
		return KiteDriverObjectType::KDOT_RENDER_OBJECT;
	}

	void KiteDriverRenderObject::Initialize()
	{
		_meshDrawer->SetMesh(_mesh);
		_meshDrawer->BindData();

		_material->Link();
		AssignUniformValue();
	}
	void KiteDriverRenderObject::Render()
	{
		_meshDrawer->Render(_material.get());
	}


	bool KiteDriverRenderObject::RayCast(kite_math::Ray ray, kite_math::RayCastInfo & raycastinfo)
	{
		kite_math::Ray mesh_coord_ray;
		auto mesh_coord_origin = _inverse_world * kite_math::Vector4f(ray.get_origin(), 1.0f);
		mesh_coord_ray.set_origin(kite_math::Vector3f(mesh_coord_origin.values));
		auto mesh_coord_direct = _inverse_world * kite_math::Vector4f(ray.get_direction(), 0.0f);
		mesh_coord_ray.set_direction(kite_math::Vector3f(mesh_coord_direct.values));
		mesh_coord_ray.set_length(ray.get_length());

		if (_mesh->RayCast(mesh_coord_ray, raycastinfo))
		{
			return true;
		}

		return false;
	}

	void KiteDriverRenderObject::RefreshWorldMatrix()
	{
		KiteDriverDummy::RefreshWorldMatrix();
		AssignUniformValue();
	}

	void KiteDriverRenderObject::AssignUniformValue()
	{
	}

}