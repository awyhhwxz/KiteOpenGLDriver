#pragma once

#include "IMouseButtonController.h"

namespace kite_driver
{
	class MouseObjectSelectController : public IMouseButtonController
	{
	public:
		MouseObjectSelectController();
		~MouseObjectSelectController();

		virtual void OnButtonDown(const kite_math::Vector2f& screen_pos) override;


		virtual void OnButtonUp(const kite_math::Vector2f& screen_pos) override;


		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) override;

	};

}