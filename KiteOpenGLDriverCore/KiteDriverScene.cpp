#include "stdafx.h"
#include "KiteDriverScene.h"

namespace kite_driver
{
	KiteDriverScene::KiteDriverScene()
	{
		_skybox = std::make_shared<KiteDriverSkyBox>();
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
		RenderSkyBox();

		std::for_each(_renderObjList.begin(), _renderObjList.end(), [this](std::weak_ptr<kite_driver::KiteDriverRenderObject> renderObjWeak)
		{
			if (!renderObjWeak.expired())
			{
				auto renderObj = renderObjWeak.lock();
				RenderObject(renderObj.get());
			}
		});
	}

	void KiteDriverScene::SetSkyBox(const std::shared_ptr<KiteDriverTextureCube>& texCube)
	{
		_skybox->SetTextureCube(texCube);
	}

	void KiteDriverScene::AssignUniformValue(kite_driver::KiteDriverRenderObject* renderObject)
	{
		auto material = renderObject->get_material();
		if (material != nullptr)
		{
			auto modelMatrix = renderObject->get_world_matrix();
			material->SetUniformValue("model_matrix", KDPVT_MATRIX4F, modelMatrix.values);
			auto viewMatrix = _camera->get_view_matrix();
			auto mvMatrix = viewMatrix * modelMatrix;
			material->SetUniformValue("mv", KDPVT_MATRIX4F, mvMatrix.values);
			auto perspectiveMatrix = _camera->get_perspective_matrix();
			auto mvpMatrix = perspectiveMatrix * mvMatrix;
			material->SetUniformValue("mvp", KDPVT_MATRIX4F, mvpMatrix.values);
		}
	}

	void KiteDriverScene::RenderSkyBox()
	{
		auto renderObject = _skybox->GetRenderObject();
		if (renderObject)
		{
			auto material = renderObject->get_material();
			if (material != nullptr)
			{
				auto mvp_matrix = _camera->get_skybox_vp_matrix();
				material->SetUniformValue("mvp", KDPVT_MATRIX4F, mvp_matrix.values);
				renderObject->Render();
			}
		}
	}

	void KiteDriverScene::RenderObject(kite_driver::KiteDriverRenderObject* object)
	{
		AssignUniformValue(object);
		object->Render();
	}

}