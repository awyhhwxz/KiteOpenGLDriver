#pragma once


namespace kite_driver
{
	class KiteDriverGraphics
	{
	public:
		KiteDriverGraphics();
		~KiteDriverGraphics();

		static void Blit(const KiteDriverRenderTexturePtr& src, KiteDriverFrameBuffer* dest);
		static void Blit(const KiteDriverRenderTexturePtr& src, KiteDriverFrameBuffer* dest, const KiteDriverMaterialPtr& material);

		static void DefaultClear();
	};

}