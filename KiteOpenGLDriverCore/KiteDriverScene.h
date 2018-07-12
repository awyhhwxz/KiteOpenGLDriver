#pragma once
namespace kite_driver
{
	class KiteDriverScene
	{
	public:
		KiteDriverScene();
		~KiteDriverScene();

		void set_camera(const std::shared_ptr<kite_driver::KiteDriverCamera>& cam) { _camera = cam; }
		kite_driver::KiteDriverCamera* get_camera() { return _camera.get(); }

		void AddRenderObj(const std::shared_ptr<kite_driver::KiteDriverRenderObject> renderObj);
		void Render();

	protected:
		void AssignUniformValue(kite_driver::KiteDriverRenderObject* renderObj);

	private:
		std::shared_ptr<kite_driver::KiteDriverCamera> _camera;
		std::vector <std::weak_ptr<kite_driver::KiteDriverRenderObject>> _renderObjList;
	};
}
