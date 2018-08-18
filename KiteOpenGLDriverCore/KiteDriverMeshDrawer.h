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
		void ResetVboCount(int vbo_count);
		void ReleaseVboBuffer();
	private:
		std::shared_ptr<KiteDriverMesh> _mesh;
		std::unique_ptr<GLuint[]> _vbo;
		int _vbo_count;

		int _vertex_vbo_index;
		int _normal_vbo_index;
		int _indices_index;
		int _uv_vbo_index;
	};

	typedef std::shared_ptr<KiteDriverMeshDrawer> KiteDriverMeshDrawerPtr;
}
