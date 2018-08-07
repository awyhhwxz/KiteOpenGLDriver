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
			OnWindowSizeChanged();
		}
		float get_window_width() { return _window_width; }

		void set_window_height(float window_height) 
		{
			_window_height = window_height;
			OnWindowSizeChanged();
		}
		float get_window_height() { return _window_height; }

		KiteDriverEvent<float, float> WindowSizeChangedEvent;

		void Refresh();

		KiteDriverScene* get_window_scene() { return _window_scene.lock().get(); }
		void set_window_scene(KiteDriverScenePtr scene) { _window_scene = scene; }
	protected:
		void OnWindowSizeChanged();
	private:

		float _window_width;
		float _window_height;

		std::weak_ptr<KiteDriverScene> _window_scene;
	};

}