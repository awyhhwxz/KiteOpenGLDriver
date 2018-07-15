#pragma once

#include "IMouseButtonController.h"

namespace kite_driver
{
	class KiteDriverMouseController;

	class MouseRightButtonController : public IMouseButtonController
	{
	public:
		MouseRightButtonController(KiteDriverMouseController* mouse_controller);
		~MouseRightButtonController();

	public:
		virtual void OnButtonDown(const kite_math::Vector2f& screen_pos) override;


		virtual void OnButtonUp(const kite_math::Vector2f& screen_pos) override;


		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) override;

	private:
		kite_math::Vector2f _preFramePos;
		float _xEuler;
		float _yEuler;
		float _rotateCoefficient;
	};
}

