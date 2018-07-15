#pragma once

namespace kite_driver
{
	class KITE_OPENGL_DRIVER_CORE_API KiteDriverInputManager : public Singleton<KiteDriverInputManager>
	{

	public:
		void RegistryMouseMessageReceiver(std::shared_ptr<IMouseMessageReceiver> receiver);

		void InvokeButtonDown(MouseButtonType button_type, const kite_math::Vector2f& screen_pos);
		void InvokeButtonUp(MouseButtonType button_type, const kite_math::Vector2f& screen_pos);
		void InvokeMouseMove(const kite_math::Vector2f& screen_pos);
		void OnMouseWheelRoll(float rollVal);
	private:
		std::vector<std::shared_ptr<IMouseMessageReceiver>> _mouseMessageReceiver;

	};
}

