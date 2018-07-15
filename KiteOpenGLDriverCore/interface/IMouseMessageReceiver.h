#pragma once

namespace kite_driver
{
	enum MouseButtonType
	{
		MBT_NONE = 0,
		MBT_LEFT = 1,
		MBT_MIDDLE = 2,
		MBT_RIGHT = 3,
	};

	class KITE_OPENGL_DRIVER_CORE_API IMouseMessageReceiver
	{
	public:
		virtual void OnButtonDown(MouseButtonType button_type, const kite_math::Vector2f& screen_pos) = 0;
		virtual void OnButtonUp(MouseButtonType button_type, const kite_math::Vector2f& screen_pos) = 0;
		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) = 0;
		virtual void OnMouseWheelRoll(float rollVal) = 0;
	};
}