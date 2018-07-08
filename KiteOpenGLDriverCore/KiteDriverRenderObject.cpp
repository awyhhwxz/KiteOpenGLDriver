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
		_meshDrawer->SetMesh(Mesh);
		_meshDrawer->BindData();

		Material->Link();
		AssignUniformValue();
	}
	void KiteDriverRenderObject::Render()
	{
		Material->BeginRender();
		{
			_meshDrawer->DrawMesh();
		}
		Material->EndRender();
	}


	void KiteDriverRenderObject::RefreshWorldMatrix()
	{
		KiteDriverDummy::RefreshWorldMatrix();
		AssignUniformValue();
	}

	void KiteDriverRenderObject::AssignUniformValue()
	{
		auto modelMatrix = _world.values; 
		if (Material.get() != nullptr)
		{
			Material->SetUniformValue("model_matrix", KDPVT_MATRIX4F, modelMatrix);
		}
	}

}