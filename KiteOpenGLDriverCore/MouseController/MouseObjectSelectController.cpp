#include "stdafx.h"
#include "MouseObjectSelectController.h"

namespace kite_driver
{
	MouseObjectSelectController::MouseObjectSelectController()
	{
	}


	MouseObjectSelectController::~MouseObjectSelectController()
	{
	}

	void MouseObjectSelectController::OnButtonDown(const kite_math::Vector2f& screen_pos)
	{
		auto scene = KiteDriverWindowManager::Instance()->get_window_scene();
		auto camera = scene->get_camera();
		auto ray = camera->GenerateRayFromScreenPos(screen_pos);

		bool is_cast = false;
		const auto& render_obj_list = scene->get_render_obj_list();
		std::for_each(render_obj_list.begin(), render_obj_list.end()
			, [&is_cast, ray](const std::weak_ptr<kite_driver::KiteDriverRenderObject>& obj)
		{
			kite_math::RayCastInfo castinfo;
			if (!obj.expired())
			{
				if (obj.lock()->RayCast(ray, castinfo))
				{
					is_cast = true;
					KiteDriverHighLightingManager::Instance()->HighLightingSingleObj(obj.lock());
				}
			}
		});

		if (!is_cast)
		{
			KiteDriverHighLightingManager::Instance()->Clear();
		}
	}

	void MouseObjectSelectController::OnButtonUp(const kite_math::Vector2f& screen_pos)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void MouseObjectSelectController::OnMouseMove(const kite_math::Vector2f& screen_pos)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}