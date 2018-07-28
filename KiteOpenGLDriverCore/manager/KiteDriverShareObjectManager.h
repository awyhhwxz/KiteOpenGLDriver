#pragma once

namespace kite_driver
{
	class KiteDriverShareObjectManager : public Singleton<KiteDriverShareObjectManager>
	{
	public:
		KiteDriverShareObjectManager();
		~KiteDriverShareObjectManager();

		KiteDriverMeshDrawer* get_fullscreen_plane();
		KiteDriverMaterialPtr get_texture_material();
	private:
		void InitializeFullScreenPlane();
		void InitializeTextureMaterial();
	private:
		KiteDriverMaterialPtr _texture_material;
		KiteDriverMeshDrawerPtr _fullscreen_plane_drawer;
	};
}
