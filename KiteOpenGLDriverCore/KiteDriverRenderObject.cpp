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


	void KiteDriverRenderObject::RefreshWorldMatrix()
	{
		KiteDriverDummy::RefreshWorldMatrix();
		AssignUniformValue();
	}

	void KiteDriverRenderObject::AssignUniformValue()
	{
	}

}