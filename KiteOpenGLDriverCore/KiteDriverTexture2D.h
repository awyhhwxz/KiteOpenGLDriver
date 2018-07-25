#pragma once

#include "KiteDriverTexture.h"

namespace kite_driver
{
	class KiteDriverTexture2D : public KiteDriverTexture
	{
	public:
		KiteDriverTexture2D();
		~KiteDriverTexture2D();

	public:

		void Assign(kite_util::ImageLoader* loader);
		void SetPixels(uint8* data, uint32 data_size);

	protected:
		virtual void SetGLData() override;

	private:
		std::unique_ptr<uint8[]> _data;
	};

	typedef std::shared_ptr<KiteDriverTexture2D> KiteDriverTexture2DPtr;
}