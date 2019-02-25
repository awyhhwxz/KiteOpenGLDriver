#pragma once

namespace kite_driver
{
	enum KiteDriverLightType
	{
		Direction,
	};

	class IKiteDriverLight
	{
	public:
		virtual KiteDriverLightType get_type() = 0;

		virtual float get_intensity() = 0;
		virtual void set_intensity(float val) = 0;
	};
}

