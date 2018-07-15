#pragma once

namespace kite_driver
{
	class KiteDriverWindowManager : public Singleton<KiteDriverWindowManager>
	{
	public:
		KiteDriverWindowManager();
		~KiteDriverWindowManager();

		void SetWindowWidthAndHeight(float width, float height);

		void set_window_width(float window_width) 
		{
			_window_width = window_width;
			RefreshWindowCameraAspect();
		}
		float get_window_width() { return _window_width; }

		void set_window_height(float window_height) 
		{
			_window_height = window_height;
			RefreshWindowCameraAspect();
		}
		float get_window_height() { return _window_height; }

		void set_window_camera(const KiteDriverCameraPtr& camera) 
		{
			_window_camera = camera; 
			RefreshWindowCameraAspect();
		}

	protected:
		void RefreshWindowCameraAspect();

	private:
		KiteDriverCameraPtr _window_camera;

		float _window_width;
		float _window_height;
	};

}