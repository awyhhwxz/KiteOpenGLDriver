#pragma once

namespace kite_driver
{
	class KiteDriverHighLightingPostEffect : public IKiteDriverPostEffect
	{
	public:
		KiteDriverHighLightingPostEffect();
		~KiteDriverHighLightingPostEffect();

		virtual void OnRenderImage(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest) override;

	private:

		void InitializeAdditionMaterial();

		KiteDriverMaterialPtr _addition_material;
	};

}