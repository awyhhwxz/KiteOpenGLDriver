#pragma once

namespace kite_driver
{
	class KiteDriverSkyBox
	{
	public:
		KiteDriverSkyBox();
		~KiteDriverSkyBox();

	public:
		void SetTextureCube(const std::shared_ptr<KiteDriverTextureCube>& texCube);
		KiteDriverRenderObject* GetRenderObject();

	private:
		bool IsEmpty();

	private:
		std::shared_ptr<KiteDriverTextureCube> _textureCube;
		std::shared_ptr<KiteDriverMaterial> _material;
		std::shared_ptr<KiteDriverMesh> _mesh;
		KiteDriverRenderObject _object;
	};

}