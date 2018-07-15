#pragma once

#include "IMouseButtonController.h"

namespace kite_driver
{
	class KiteDriverMouseController;

	class MouseMiddleButtonController : public IMouseButtonController
	{
	public:
		MouseMiddleButtonController(KiteDriverMouseController* mouse_controller);
		~MouseMiddleButtonController();

		virtual void OnButtonDown(const kite_math::Vector2f& screen_pos) override;


		virtual void OnButtonUp(const kite_math::Vector2f& screen_pos) override;


		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) override;

	private:
		float _moveCoefficient;
		kite_math::Vector2f _preFramePos;
	};
}