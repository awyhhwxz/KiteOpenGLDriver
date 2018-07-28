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

		material->BeginRender();
		{
			plane->DrawMesh();
		}
		material->EndRender();

		dest->EndRender();
	}

	void KiteDriverGraphics::DefaultClear()
	{
		glDepthMask(true);
		glClearColor(1.0f, 0.0f, 0.0f, 1.f);
		glClearDepth(1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

}