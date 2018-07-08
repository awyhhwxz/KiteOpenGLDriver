#pragma once

namespace kite_driver
{

	class KiteDriverRenderObject : public KiteDriverDummy
	{
	public:
		KiteDriverRenderObject();
		~KiteDriverRenderObject();

	public:
		void Initialize();
		void Render();

		std::shared_ptr<KiteDriverMaterial> Material;
		std::shared_ptr<KiteDriverMesh> Mesh;

	protected:
		void RefreshWorldMatrix() override;

	private:
		void AssignUniformValue();

	private:
		std::shared_ptr<KiteDriverMeshDrawer> _meshDrawer;
	};

}