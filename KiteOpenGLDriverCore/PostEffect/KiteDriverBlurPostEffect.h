#pragma once

#include "KiteDriverTextureBlurDrawer.h"

namespace kite_driver
{
	class KiteDriverBlurPostEffect : public IKiteDriverPostEffect
	{
	public:
		KiteDriverBlurPostEffect();
		~KiteDriverBlurPostEffect();

		virtual void OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest) override;

	private:
		KiteDriverTextureBlurDrawer _blur_drawer;
	};

}