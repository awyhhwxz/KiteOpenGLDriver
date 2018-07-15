#include "stdafx.h"
#include "MouseRightButtonController.h"
#include "KiteDriverMouseController.h"

namespace kite_driver
{
	MouseRightButtonController::MouseRightButtonController(kite_driver::KiteDriverMouseController* mouse_controller)
		: _xEuler(0), _yEuler(0), _rotateCoefficient(50)
	{
		_mouse_controller = mouse_controller;
	}


	MouseRightButtonController::~MouseRightButtonController()
	{
	}

	void MouseRightButtonController::OnButtonDown(const kite_math::Vector2f& screen_pos)
	{
		_preFramePos = screen_pos;
	}

	void MouseRightButtonController::OnButtonUp(const kite_math::Vector2f& screen_pos)
	{
		_preFramePos = screen_pos;
	}

	void MouseRightButtonController::OnMouseMove(const kite_math::Vector2f& screen_pos)
	{

		auto camera = _mouse_controller->GetCamera();
		if (camera)
		{
			auto delta_move = screen_pos - _preFramePos;
			delta_move = delta_move / _rotateCoefficient;
			_xEuler += delta_move.y;
			_yEuler += delta_move.x;

			camera->set_euler(kite_math::Euler(_xEuler, _yEuler, 0));
		}

		_preFramePos = screen_pos;
	}

}
