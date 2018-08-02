#include "stdafx.h"
#include "KiteDriverHighLightingPostEffect.h"

namespace kite_driver
{
	KiteDriverHighLightingPostEffect::KiteDriverHighLightingPostEffect()
	{
	}


	KiteDriverHighLightingPostEffect::~KiteDriverHighLightingPostEffect()
	{
	}

	void KiteDriverHighLightingPostEffect::OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest)
	{
		InitializeAdditionMaterial();
		_addition_material->SetUniformTexture("_Tex1", src);
		_addition_material->SetUniformTexture("_Tex2", KiteDriverHighLightingManager::Instance()->GetHighLightTexture());
		KiteDriverGraphics::Blit(src, dest.get(), _addition_material);
	}

	void KiteDriverHighLightingPostEffect::InitializeAdditionMaterial()
	{

		if (!_addition_material)
		{
			_addition_material = std::make_shared<KiteDriverMaterial>();
			auto vertexPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture_addition.vertex";
			auto fragmentPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture_addition.fragment";
			_addition_material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
			_addition_material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());

			_addition_material->Link();
		}
	}

}