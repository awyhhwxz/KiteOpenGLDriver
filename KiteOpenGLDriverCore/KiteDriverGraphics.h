#pragma once


namespace kite_driver
{
	class KiteDriverGraphics
	{
	public:
		KiteDriverGraphics();
		~KiteDriverGraphics();

		static void Blit(const KiteDriverRenderTexturePtr& src, const KiteDriverRenderTexturePtr& dest);
		static void Blit(const KiteDriverRenderTexturePtr& src, const KiteDriverRenderTexturePtr& dest, const KiteDriverMaterialPtr& material);
		static void Blit(const KiteDriverRenderTexturePtr& src, KiteDriverFrameBuffer* dest);
		static void Blit(const KiteDriverRenderTexturePtr& src, KiteDriverFrameBuffer* dest, const KiteDriverMaterialPtr& material);

		static void DefaultClear();
		static void DefaultClear(const kite_math::Vector4f& color);

		static void SetViewPort(const ViewPort& viewport);
	};

}