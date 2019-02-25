#pragma once

#include "IKiteDriverLight.h"

namespace kite_driver
{
	class KiteDriverCommonLight : public IKiteDriverLight
	{
	public:
		KiteDriverCommonLight();
		~KiteDriverCommonLight();

		//virtual float get_intensity() override;
		//virtual void set_intensity(float val) override;

	private:
		float _intensity;
	};

}