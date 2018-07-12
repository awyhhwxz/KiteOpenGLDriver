#include "stdafx.h"
#include "KiteDriverScene.h"

namespace kite_driver
{
	KiteDriverScene::KiteDriverScene()
	{
	}


	KiteDriverScene::~KiteDriverScene()
	{
	}

	void KiteDriverScene::AddRenderObj(const std::shared_ptr<kite_driver::KiteDriverRenderObject> renderObj)
	{
		if (std::find_if(_renderObjList.begin(), _renderObjList.end(), [renderObj](std::weak_ptr<kite_driver::KiteDriverRenderObject> renderObjWeak)
		{
			return renderObj == renderObjWeak.lock();
		}) == _renderObjList.end())
		{
			_renderObjList.push_back(renderObj);
		}
	}
	void KiteDriverScene::Render()
	{
		std::for_each(_renderObjList.begin(), _renderObjList.end(), [this](std::weak_ptr<kite_driver::KiteDriverRenderObject> renderObjWeak)
		{
			if (!renderObjWeak.expired())
			{
				auto renderObj = renderObjWeak.lock();
				AssignUniformValue(renderObj.get());
				renderObj->Render();
			}
		});
	}
	void KiteDriverScene::AssignUniformValue(kite_driver::KiteDriverRenderObject* renderObj)
	{
		auto material = renderObj->get_material();
		if (material != nullptr)
		{
			auto modelMatrix = renderObj->get_world_matrix();
			material->SetUniformValue("model_matrix", KDPVT_MATRIX4F, modelMatrix.values);
			auto viewMatrix = _camera->get_inverse_world_matrix();
			auto mvMatrix = viewMatrix * modelMatrix;
			material->SetUniformValue("mv", KDPVT_MATRIX4F, mvMatrix.values);
		}
	}
}