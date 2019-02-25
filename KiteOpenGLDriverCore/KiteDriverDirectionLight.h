#pragma once

#include "KiteDriverCommonLight.h"

namespace kite_driver
{
	class KiteDriverDirectionLight : public KiteDriverCommonLight
	{
	public:
		KiteDriverDirectionLight();
		~KiteDriverDirectionLight();

		virtual KiteDriverLightType get_type() override { return KiteDriverLightType::Direction; }
	};
}

