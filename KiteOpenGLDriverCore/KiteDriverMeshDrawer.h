#pragma once

namespace kite_driver
{
	class KiteDriverMeshDrawer
	{
	public:
		KiteDriverMeshDrawer();
		~KiteDriverMeshDrawer();

	public: 
		inline void SetMesh(std::shared_ptr<KiteDriverMesh> mesh) { _mesh = mesh; }

		void BindData();

		void Render(KiteDriverMaterial* material);

		inline const std::shared_ptr<KiteDriverMesh>& get_mesh() { return _mesh; }
	private:
		GLuint GetUVAttribIndex(int uv_index);
		void DrawMesh();

	private:
		std::shared_ptr<KiteDriverMesh> _mesh;
		std::unique_ptr<GLuint[]> _vbo;
	};

	typedef std::shared_ptr<KiteDriverMeshDrawer> KiteDriverMeshDrawerPtr;
}
