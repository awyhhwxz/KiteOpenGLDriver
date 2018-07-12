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

		void set_mesh(const std::shared_ptr<KiteDriverMesh>& mesh) { _mesh = mesh; }

		KiteDriverMaterial* get_material() { return _material.get(); }
		void set_material(const std::shared_ptr<KiteDriverMaterial>& mat) { _material = mat; }
	protected:
		std::shared_ptr<KiteDriverMaterial> _material;
		std::shared_ptr<KiteDriverMesh> _mesh;

	protected:
		void RefreshWorldMatrix() override;

	private:
		void AssignUniformValue();

	private:
		std::shared_ptr<KiteDriverMeshDrawer> _meshDrawer;
	};

}