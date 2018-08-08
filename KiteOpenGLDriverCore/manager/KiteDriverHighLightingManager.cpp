#include "stdafx.h"
#include "KiteDriverHighLightingManager.h"
#include "KiteDriverFastAccess.h"

namespace kite_driver
{
	KiteDriverHighLightingManager::KiteDriverHighLightingManager()
	{
		_render_texture = std::make_shared<KiteDriverRenderTexture>();

		_pure_color_material = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture_purecolor.vertex",
			"/shader/texture_purecolor.fragment");
		_pure_color_material->SetUniformValue("_pureColor", KDPVT_VECTOR4, kite_math::Vector4f(1.0f, 0.0f, 0.0f, 1.0f).values);
		_pure_color_material->Link();

		_substraction_material = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture_substraction.vertex",
			"/shader/texture_substraction.fragment");
		_substraction_material->Link();

		_blur_drawer.set_blur_point_size(2.0f);
	}


	KiteDriverHighLightingManager::~KiteDriverHighLightingManager()
	{
	}

	void KiteDriverHighLightingManager::AddHighLightingObj(KiteDriverRenderObjectPtr highlighting_obj)
	{
		if (std::find_if(_highlight_obj_list.begin(), _highlight_obj_list.end(), [&highlighting_obj](const std::weak_ptr<KiteDriverRenderObject>& obj)
		{
			if (obj.expired() && obj.lock().get() == highlighting_obj.get())
			{
				return true;
			}

			return false;
		}) == _highlight_obj_list.end())
		{
			_highlight_obj_list.push_back(highlighting_obj);
		}
	}

	void KiteDriverHighLightingManager::RemoveHighLightingObj(KiteDriverRenderObjectPtr highlighting_obj)
	{
		auto found_iter = std::find_if(_highlight_obj_list.begin(), _highlight_obj_list.end(), [&highlighting_obj](const std::weak_ptr<KiteDriverRenderObject>& obj)
		{
			if (obj.expired() && obj.lock().get() == highlighting_obj.get())
			{
				return true;
			}

			return false;
		});

		if (found_iter != _highlight_obj_list.end())
		{
			_highlight_obj_list.erase(found_iter);
		}
	}

	void KiteDriverHighLightingManager::Clear()
	{
		_highlight_obj_list.clear();
	}

	void KiteDriverHighLightingManager::RenderHighLighting(KiteDriverCamera* camera)
	{
		auto temp_frame_buffer = KiteDriverShareObjectManager::Instance()->GetTemporaryFrameBuffer();
		temp_frame_buffer->SetRenderTarget(_render_texture);
		temp_frame_buffer->set_view_port(camera->get_view_port());
		temp_frame_buffer->BeginRender();
		{
			KiteDriverGraphics::DefaultClear(kite_math::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));

			std::for_each(_highlight_obj_list.begin(), _highlight_obj_list.end(), [this, &camera](std::weak_ptr<kite_driver::KiteDriverRenderObject> render_obj_weak)
			{
				if (!render_obj_weak.expired())
				{
					auto render_obj = render_obj_weak.lock();
					camera->SetCameraMatrices(render_obj.get(), _pure_color_material.get());
					render_obj->get_mesh_drawer()->Render(_pure_color_material.get());
				}
			});
		}
		temp_frame_buffer->EndRender();

		auto temp_render_texture = KiteDriverShareObjectManager::Instance()->GetTemporaryRenderTexture();
		temp_frame_buffer->SetRenderTarget(temp_render_texture);
		_blur_drawer.Blur(_render_texture, temp_frame_buffer);
		
		_substraction_material->SetUniformTexture("_Tex1", temp_render_texture);
		_substraction_material->SetUniformTexture("_Tex2", _render_texture);
		auto substraction_render_texture = KiteDriverShareObjectManager::Instance()->GetTemporaryRenderTexture();
		KiteDriverGraphics::Blit(_render_texture, substraction_render_texture, _substraction_material);
		KiteDriverGraphics::Blit(substraction_render_texture, _render_texture);
		KiteDriverShareObjectManager::Instance()->ReleaseTemporaryRenderTexture(temp_render_texture);
		KiteDriverShareObjectManager::Instance()->ReleaseTemporaryRenderTexture(substraction_render_texture);
		KiteDriverShareObjectManager::Instance()->ReleaseTemporaryFrameBuffer(temp_frame_buffer);
	}

	const kite_driver::KiteDriverRenderTexturePtr& KiteDriverHighLightingManager::GetHighLightTexture()
	{
		return _render_texture;
	}

	void KiteDriverHighLightingManager::HighLightingSingleObj(KiteDriverRenderObjectPtr highlighting_obj)
	{
		Clear();
		AddHighLightingObj(highlighting_obj);
	}

}