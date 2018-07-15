#pragma once

namespace kite_driver
{
	class KiteDriverMouseController;
	class IMouseButtonController
	{
	public:
		virtual void OnButtonDown(const kite_math::Vector2f& screen_pos) = 0;


		virtual void OnButtonUp(const kite_math::Vector2f& screen_pos) = 0;


		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) = 0;
		
	protected:
		KiteDriverMouseController* _mouse_controller;
	};

	typedef std::shared_ptr<IMouseButtonController> IMouseButtonControllerPtr;
}