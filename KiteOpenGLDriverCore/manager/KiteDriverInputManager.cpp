#include "stdafx.h"
#include "KiteDriverInputManager.h"

namespace kite_driver
{
	void KiteDriverInputManager::RegistryMouseMessageReceiver(std::shared_ptr<IMouseMessageReceiver> receiver)
	{
		_mouseMessageReceiver.push_back(receiver);
	}
	void KiteDriverInputManager::InvokeButtonDown(MouseButtonType button_type, const kite_math::Vector2f & screen_pos)
	{
		std::for_each(_mouseMessageReceiver.begin(), _mouseMessageReceiver.end(), [button_type, &screen_pos](const std::shared_ptr<IMouseMessageReceiver>& receiver)
		{
			receiver->OnButtonDown(button_type, screen_pos);
		});
	}
	void KiteDriverInputManager::InvokeButtonUp(MouseButtonType button_type, const kite_math::Vector2f & screen_pos)
	{
		std::for_each(_mouseMessageReceiver.begin(), _mouseMessageReceiver.end(), [button_type, &screen_pos](const std::shared_ptr<IMouseMessageReceiver>& receiver)
		{
			receiver->OnButtonUp(button_type, screen_pos);
		});
	}
	void KiteDriverInputManager::InvokeMouseMove(const kite_math::Vector2f & screen_pos)
	{
		std::for_each(_mouseMessageReceiver.begin(), _mouseMessageReceiver.end(), [&screen_pos](const std::shared_ptr<IMouseMessageReceiver>& receiver)
		{
			receiver->OnMouseMove(screen_pos);
		});
	}
	void KiteDriverInputManager::OnMouseWheelRoll(float rollVal)
	{
		std::for_each(_mouseMessageReceiver.begin(), _mouseMessageReceiver.end(), [&rollVal](const std::shared_ptr<IMouseMessageReceiver>& receiver)
		{
			receiver->OnMouseWheelRoll(rollVal);
		});
	}
}