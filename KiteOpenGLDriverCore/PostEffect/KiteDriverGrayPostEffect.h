#pragma once

namespace kite_driver
{
	class KiteDriverGrayPostEffect : public IKiteDriverPostEffect
	{
	public:
		KiteDriverGrayPostEffect();
		~KiteDriverGrayPostEffect();

		virtual void OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest) override;

	private:
		void InitializeGrayMaterial();

		KiteDriverMaterialPtr _gray_material;
	};

}