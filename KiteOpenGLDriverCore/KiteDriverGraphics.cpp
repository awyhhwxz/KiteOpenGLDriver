#include "stdafx.h"
#include "KiteDriverGraphics.h"
#include "KiteDriverMaterial.h"
#include "KiteDriverMeshDrawer.h"

namespace kite_driver
{
	KiteDriverGraphics::KiteDriverGraphics()
	{
	}


	KiteDriverGraphics::~KiteDriverGraphics()
	{
	}

	void KiteDriverGraphics::Blit(const KiteDriverRenderTexturePtr & src, KiteDriverFrameBuffer * dest)
	{
		auto material = KiteDriverShareObjectManager::Instance()->get_texture_material();		
		material->SetUniformTexture("tex", src);
		Blit(src, dest, material);
	}

	void KiteDriverGraphics::Blit(const KiteDriverRenderTexturePtr& src, KiteDriverFrameBuffer * dest, const KiteDriverMaterialPtr& material)
	{
		dest->BeginRender();

		DefaultClear();
		auto plane = KiteDriverShareObjectManager::Instance()->get_fullscreen_plane();

		auto matrix = kite_math::Matrix4f::Identity;// kite_math::Matrix4f::Translate(kite_math::Vector3f(0.5, 0.5, 0.5));

		material->SetUniformValue("mvp", KDPVT_MATRIX4F, const_cast<float*>(matrix.values));

		plane->Render(material.get());

		dest->EndRender();
	}

	void KiteDriverGraphics::Blit(const KiteDriverRenderTexturePtr& src, const KiteDriverRenderTexturePtr& dest)
	{
		auto temp_frame_buffer = KiteDriverShareObjectManager::Instance()->GetTemporaryFrameBuffer();
		temp_frame_buffer->SetRenderTarget(dest);
		Blit(src, temp_frame_buffer.get());
		KiteDriverShareObjectManager::Instance()->ReleaseTemporaryFrameBuffer(temp_frame_buffer);
	}

	void KiteDriverGraphics::Blit(const KiteDriverRenderTexturePtr& src, const KiteDriverRenderTexturePtr& dest, const KiteDriverMaterialPtr& material)
	{
		auto temp_frame_buffer = KiteDriverShareObjectManager::Instance()->GetTemporaryFrameBuffer();
		temp_frame_buffer->SetRenderTarget(dest);
		Blit(src, temp_frame_buffer.get(), material);
		KiteDriverShareObjectManager::Instance()->ReleaseTemporaryFrameBuffer(temp_frame_buffer);
	}

	void KiteDriverGraphics::DefaultClear()
	{
		glDepthMask(true);
		DefaultClear(kite_math::Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		glClearDepth(1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

	void KiteDriverGraphics::DefaultClear(const kite_math::Vector4f& color)
	{
		glDepthMask(true);
		glClearColor(color.x, color.y, color.z, color.w);
		glClearDepth(1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

	void KiteDriverGraphics::SetViewPort(const ViewPort& viewport)
	{
		glViewport(viewport.get_x(), viewport.get_y(), viewport.get_width(), viewport.get_height());
	}

}