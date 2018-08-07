#include "stdafx.h"
#include "KiteDriverScene.h"

namespace kite_driver
{
	KiteDriverScene::KiteDriverScene()
	{
		_skybox = std::make_shared<KiteDriverSkyBox>();
		_frame_buffer = std::make_shared<KiteDriverFrameBuffer>();
		_post_effect_frame_buffer = std::make_shared<KiteDriverFrameBuffer>();
	}


	KiteDriverScene::~KiteDriverScene()
	{
	}

	void KiteDriverScene::AddRenderObj(const std::shared_ptr<kite_driver::KiteDriverRenderObject> renderObj)
	{
		if (std::find_if(_render_obj_list.begin(), _render_obj_list.end(), [renderObj](const std::weak_ptr<kite_driver::KiteDriverRenderObject>& renderObjWeak)
		{
			return renderObj == renderObjWeak.lock();
		}) == _render_obj_list.end())
		{
			_render_obj_list.push_back(renderObj);
		}
	}
	void KiteDriverScene::Render()
	{
		glEnable(GL_MULTISAMPLE);
		bool posteffect_isnull = _post_effect.get() == nullptr;
		auto& render_framebuffer = posteffect_isnull ? _frame_buffer : _post_effect_frame_buffer;

		const auto& view_port = _camera->get_view_port();
		render_framebuffer->set_view_port(view_port);
		render_framebuffer->BeginRender();
		{
			RenderAllObjects();
		}
		render_framebuffer->EndRender();

		if (!posteffect_isnull)
		{
			_frame_buffer->set_view_port(view_port);
			_post_effect->OnRenderImage(render_framebuffer->GetRenderTarget(), _frame_buffer);
		}
	}

	void KiteDriverScene::RenderAllObjects()
	{
		ClearScreen();
		RenderSkyBox();

		std::for_each(_render_obj_list.begin(), _render_obj_list.end(), [this](std::weak_ptr<kite_driver::KiteDriverRenderObject> render_obj_weak)
		{
			if (!render_obj_weak.expired())
			{
				auto render_obj = render_obj_weak.lock();
				RenderObject(render_obj.get());
			}
		});
	}

	void KiteDriverScene::ClearScreen()
	{
		KiteDriverGraphics::DefaultClear();
	}

	void KiteDriverScene::SetSkyBox(const KiteDriverTextureCubePtr& texCube)
	{
		_skybox->SetTextureCube(texCube);
	}

	void KiteDriverScene::SetRenderTarget(const KiteDriverRenderTexturePtr & render_target)
	{
		_frame_buffer->SetRenderTarget(render_target);
	}

	void KiteDriverScene::SetPostEffect(const IKiteDriverPostEffectPtr & effect)
	{
		_post_effect = effect;

		if (_post_effect_frame_buffer->GetRenderTarget() == nullptr)
		{
			_post_effect_frame_buffer->SetRenderTarget(std::make_shared<KiteDriverRenderTexture>());
		}
	}

	void KiteDriverScene::AssignUniformValue(kite_driver::KiteDriverRenderObject* render_object)
	{
		_camera->SetCameraMatrices(render_object);
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