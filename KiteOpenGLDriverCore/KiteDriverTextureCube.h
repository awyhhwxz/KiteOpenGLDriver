#pragma once

#include "KiteDriverTexture.h"

namespace kite_driver
{
	class KiteDriverTextureCube : public KiteDriverTexture
	{
	public:
		KiteDriverTextureCube();
		~KiteDriverTextureCube();
		
		void Assign(kite_util::ImageLoader loader[6]);

	private:
		void SetGLData();

	private:
		std::unique_ptr<uint8[]> _datas[6];
	};

	typedef std::shared_ptr<KiteDriverTextureCube> KiteDriverTextureCubePtr;
}