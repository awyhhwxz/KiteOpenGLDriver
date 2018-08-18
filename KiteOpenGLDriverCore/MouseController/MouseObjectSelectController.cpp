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
		throw std::logic_error("The method or operation is not implemented.");
	}

	void MouseObjectSelectController::OnButtonUp(const kite_math::Vector2f& screen_pos)
	{
		auto scene = KiteDriverWindowManager::Instance()->get_window_scene();
		auto camera = scene->get_camera();
		auto ray = camera->GenerateRayFromScreenPos(screen_pos);

		bool is_cast = false;
		const auto& render_obj_list = scene->get_render_obj_list();
		
		kite_driver::KiteDriverRenderObjectPtr select_obj;
		float distance = kite_math::Mathf::kFloatMaxValue;
		std::for_each(render_obj_list.begin(), render_obj_list.end()
			, [&is_cast, ray, &distance, &select_obj](const std::weak_ptr<kite_driver::KiteDriverRenderObject>& obj)
		{
			if (!obj.expired())
			{
				kite_math::RayCastInfo castinfo;
				if (obj.lock()->RayCast(ray, castinfo))
				{
					if (castinfo.Distance < distance)
					{
						distance = castinfo.Distance;
						select_obj = obj.lock();
						is_cast = true;
					}
				}
			}
		});

		if (is_cast)
		{
			KiteDriverHighLightingManager::Instance()->HighLightingSingleObj(select_obj);
		}
		else
		{
			KiteDriverHighLightingManager::Instance()->Clear();
		}
	}

	void MouseObjectSelectController::OnMouseMove(const kite_math::Vector2f& screen_pos)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}