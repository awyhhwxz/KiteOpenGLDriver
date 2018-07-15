#include "stdafx.h"
#include "MouseMiddleButtonController.h"
#include "KiteDriverMouseController.h"

namespace kite_driver
{
	MouseMiddleButtonController::MouseMiddleButtonController(KiteDriverMouseController* mouse_controller)
		: _moveCoefficient(20)
	{
		_mouse_controller = mouse_controller;
	}


	MouseMiddleButtonController::~MouseMiddleButtonController()
	{
	}

	void MouseMiddleButtonController::OnButtonDown(const kite_math::Vector2f& screen_pos)
	{
		_preFramePos = screen_pos;
	}

	void MouseMiddleButtonController::OnButtonUp(const kite_math::Vector2f& screen_pos)
	{
		_preFramePos = screen_pos;
	}

	void MouseMiddleButtonController::OnMouseMove(const kite_math::Vector2f& screen_pos)
	{
		auto camera = _mouse_controller->GetCamera();
		if (camera)
		{
			auto delta_move = screen_pos - _preFramePos;
			delta_move = delta_move / _moveCoefficient;

			camera->Translate(kite_math::Vector3f(delta_move, 0));
		}

		_preFramePos = screen_pos;
	}

}