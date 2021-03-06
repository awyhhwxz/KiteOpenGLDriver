#pragma once

namespace kite_driver
{

	class KiteDriverRenderObject : public KiteDriverDummy
	{
	public:
		KiteDriverRenderObject();
		~KiteDriverRenderObject();

	public:
		virtual KiteDriverObjectType get_type() override;

	public:
		void Initialize();
		void Render();

		void set_mesh(const std::shared_ptr<KiteDriverMesh>& mesh) { _mesh = mesh; }
		KiteDriverMeshDrawer* get_mesh_drawer() { return _meshDrawer.get(); }

		KiteDriverMaterial* get_material() { return _material.get(); }
		void set_material(const std::shared_ptr<KiteDriverMaterial>& mat) { _material = mat; }

		bool RayCast(kite_math::Ray ray, kite_math::RayCastInfo& raycastinfo);
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

	typedef std::shared_ptr<KiteDriverRenderObject> KiteDriverRenderObjectPtr;
}