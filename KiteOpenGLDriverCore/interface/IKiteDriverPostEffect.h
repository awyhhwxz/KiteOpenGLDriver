#pragma once

namespace kite_driver
{
	class IKiteDriverPostEffect
	{
	public:
		virtual void OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest) = 0;
	};

	typedef std::shared_ptr<IKiteDriverPostEffect> IKiteDriverPostEffectPtr;
}