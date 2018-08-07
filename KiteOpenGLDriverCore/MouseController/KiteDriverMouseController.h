#pragma once

#include "IMouseButtonController.h"
#include "MouseObjectSelectController.h"

namespace kite_driver
{
	class KiteDriverMouseController : public IMouseMessageReceiver
	{
	public:
		KiteDriverMouseController();
		~KiteDriverMouseController();

		virtual void OnButtonDown(MouseButtonType button_type, const kite_math::Vector2f& screen_pos) override;


		virtual void OnButtonUp(MouseButtonType button_type, const kite_math::Vector2f& screen_pos) override;


		virtual void OnMouseMove(const kite_math::Vector2f& screen_pos) override;

		kite_driver::KiteDriverCamera* GetCamera() { return _camera.lock().get(); }
		void SetCamera(KiteDriverCameraPtr camera) { _camera = camera; }

		virtual void OnMouseWheelRoll(float rollVal) override;

	protected:
		IMouseButtonController * GetButtonController(MouseButtonType button_type);

	private:
		std::weak_ptr<kite_driver::KiteDriverCamera> _camera;
		std::map<MouseButtonType, bool> _isButtonDown;
		std::map<MouseButtonType, IMouseButtonControllerPtr> _controllerMatch;
		MouseObjectSelectController _select_controller;
	};
}

