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
		KiteDriverGraphics::Blit(src, dest.get());
		
	}
}