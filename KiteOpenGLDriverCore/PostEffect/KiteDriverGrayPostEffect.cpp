#include "stdafx.h"
#include "KiteDriverGrayPostEffect.h"


namespace kite_driver
{

	KiteDriverGrayPostEffect::KiteDriverGrayPostEffect()
	{
	
	}


	KiteDriverGrayPostEffect::~KiteDriverGrayPostEffect()
	{
	}

	void KiteDriverGrayPostEffect::OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest)
	{
		InitializeGrayMaterial();
		_gray_material->SetUniformTexture("tex", src);
		KiteDriverGraphics::Blit(src, dest.get(), _gray_material);		
	}

	void KiteDriverGrayPostEffect::InitializeGrayMaterial()
	{
		if (!_gray_material)
		{
			_gray_material = std::make_shared<KiteDriverMaterial>();
			auto vertexPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture.vertex";
			auto fragmentPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture_gray.fragment";
			_gray_material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
			_gray_material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());

			_gray_material->Link();
		}
	}

}