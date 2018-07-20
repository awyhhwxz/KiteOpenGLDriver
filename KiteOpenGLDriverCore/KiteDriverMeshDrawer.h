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

		void DrawMesh();

	private:
		GLuint GetUVAttribIndex(int uv_index);

	private:
		std::shared_ptr<KiteDriverMesh> _mesh;
		std::unique_ptr<GLuint[]> _vbo;
	};
}
