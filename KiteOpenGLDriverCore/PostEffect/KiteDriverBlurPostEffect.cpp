#include "stdafx.h"
#include "KiteDriverBlurPostEffect.h"

namespace kite_driver
{
	KiteDriverBlurPostEffect::KiteDriverBlurPostEffect()
	{
	}


	KiteDriverBlurPostEffect::~KiteDriverBlurPostEffect()
	{
	}

	void KiteDriverBlurPostEffect::OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest)
	{
		_blur_drawer.Blur(src, dest);
	}

}