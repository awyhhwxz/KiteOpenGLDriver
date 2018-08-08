#include "stdafx.h"
#include "KiteDriverMouseController.h"
#include "MouseRightButtonController.h"
#include "MouseMiddleButtonController.h"

namespace kite_driver
{
	KiteDriverMouseController::KiteDriverMouseController()
	{
		_controllerMatch.insert(std::make_pair(MouseButtonType::MBT_RIGHT, std::make_shared<MouseRightButtonController>(this)));
		_controllerMatch.insert(std::make_pair(MouseButtonType::MBT_MIDDLE, std::make_shared<MouseMiddleButtonController>(this)));
	}


	KiteDriverMouseController::~KiteDriverMouseController()
	{
	}

	void KiteDriverMouseController::OnButtonDown(MouseButtonType button_type, const kite_math::Vector2f& screen_pos)
	{
		_isButtonDown[button_type] = true;
		auto controller = GetButtonController(button_type);
		if (controller) controller->OnButtonDown(screen_pos);
	}

	void KiteDriverMouseController::OnButtonUp(MouseButtonType button_type, const kite_math::Vector2f& screen_pos)
	{
		_isButtonDown[button_type] = false;
		auto controller = GetButtonController(button_type);
		if (controller) controller->OnButtonUp(screen_pos);
		if (button_type == MouseButtonType::MBT_LEFT) _select_controller.OnButtonUp(screen_pos);
	}

	void KiteDriverMouseController::OnMouseMove(const kite_math::Vector2f& screen_pos)
	{
		std::for_each(_isButtonDown.begin(), _isButtonDown.end(), [this, screen_pos](const std::pair<MouseButtonType, bool>& pair)
		{
			auto btype = pair.first;
			auto is_down = pair.second;
			if (is_down)
			{
				auto controller = GetButtonController(btype);
				if (controller) controller->OnMouseMove(screen_pos);
			}
		});
	}

	void KiteDriverMouseController::OnMouseWheelRoll(float rollVal)
	{
		auto camera = this->GetCamera();
		if (camera)
		{
			auto deltaZ = rollVal > 0 ? 1 : -1;
			camera->Translate(kite_math::Vector3f(0, 0, deltaZ));
		}
	}

	kite_driver::IMouseButtonController* KiteDriverMouseController::GetButtonController(MouseButtonType button_type)
	{
		auto controller = _controllerMatch.find(button_type);
		if (controller != _controllerMatch.end())
		{
			return controller->second.get();
		}

		return nullptr;
	}

}