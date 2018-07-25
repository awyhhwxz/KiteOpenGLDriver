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

		void SetSkyBox(const KiteDriverTextureCubePtr& texCube);
		void SetRenderTarget(const KiteDriverRenderTexturePtr& render_target);
	protected:
		void AssignUniformValue(kite_driver::KiteDriverRenderObject* renderObject);
		void RenderSkyBox();
		void ClearScreen();
		void RenderObject(kite_driver::KiteDriverRenderObject* object);
	private:
		std::shared_ptr<KiteDriverSkyBox> _skybox;
		std::shared_ptr<kite_driver::KiteDriverCamera> _camera;
		std::vector <std::shared_ptr<kite_driver::KiteDriverRenderObject>> _renderObjList;
		KiteDriverFrameBuffer _frame_buffer;
	};
}
