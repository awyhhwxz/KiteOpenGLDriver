#include "stdafx.h"
#include "KiteDriverMeshDrawer.h"

namespace kite_driver
{
	KiteDriverMeshDrawer::KiteDriverMeshDrawer()
		: _vbo_count(0),
		_vertex_vbo_index(-1),
		_normal_vbo_index(-1),
		_uv_vbo_index(-1),
		_indices_index(-1)
	{
	}


	KiteDriverMeshDrawer::~KiteDriverMeshDrawer()
	{
		ReleaseVboBuffer();
	}

	void kite_driver::KiteDriverMeshDrawer::BindData()
	{
		bool normal_isempty = _mesh->GetNormalCount() == 0;
		int vertex_vbo_count = 1;
		int index_vbo_count = 1;
		int normal_vbo_count = (normal_isempty ? 0 : 1);
		int vbo_count = vertex_vbo_count + index_vbo_count + normal_vbo_count + _mesh->GetUVChannelCount();
		ResetVboCount(vbo_count);

		auto current_vbo_index = 0;

		_vertex_vbo_index = current_vbo_index++;
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[_vertex_vbo_index]);
		auto vert = _mesh->GetVertices();
		auto verticesSize = _mesh->GetVertexCount() * sizeof(kite_math::Vector3f);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vert, GL_STATIC_DRAW);
		
		if (!normal_isempty)
		{
			_normal_vbo_index = current_vbo_index++;
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[_normal_vbo_index]);
			auto normal = _mesh->GetNormals();
			auto normalSize = _mesh->GetNormalCount() * sizeof(kite_math::Vector3f);
			glBufferData(GL_ARRAY_BUFFER, normalSize, normal, GL_STATIC_DRAW);
		}

		_indices_index = current_vbo_index++;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[_indices_index]);
		auto inde = _mesh->GetIndices();
		auto indicesSize = _mesh->GetIndexCount() * sizeof(uint16);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, inde, GL_STATIC_DRAW);

		_uv_vbo_index = current_vbo_index;
		for (int uvi = 0 ; uvi < _mesh->GetUVChannelCount() ; ++uvi)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[_uv_vbo_index + uvi]);
			auto uvs = _mesh->GetUVs(uvi);
			auto uvsSize = _mesh->GetVertexCount() * sizeof(kite_math::Vector2f);
			glBufferData(GL_ARRAY_BUFFER, uvsSize, uvs, GL_STATIC_DRAW);
		}
	}
	void KiteDriverMeshDrawer::DrawMesh()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[_vertex_vbo_index]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		
		bool normal_isempty = _mesh->GetNormalCount() == 0;
		if (!normal_isempty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[_normal_vbo_index]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}

		for (int uvi = 0; uvi < _mesh->GetUVChannelCount(); ++uvi)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[_uv_vbo_index + uvi]);

			GLuint uv_attrib_index = GetUVAttribIndex(uvi);
			glVertexAttribPointer(uv_attrib_index, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(uv_attrib_index);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[_indices_index]);
		
		glDrawElements(GL_TRIANGLES, _mesh->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		glDisableVertexAttribArray(0);
		if (!normal_isempty) glDisableVertexAttribArray(1);
		for (int uvi = 0; uvi < _mesh->GetUVChannelCount(); ++uvi)
		{
			glDisableVertexAttribArray(GetUVAttribIndex(uvi));
		}
	}

	void KiteDriverMeshDrawer::ResetVboCount(int vbo_count)
	{		
		if (vbo_count != _vbo_count)
		{
			ReleaseVboBuffer();

			_vbo_count = vbo_count;
			_vbo.reset(new GLuint[vbo_count]);
			auto vboPointer = _vbo.get();
			glGenBuffers(vbo_count, vboPointer);
		}
	}

	void KiteDriverMeshDrawer::ReleaseVboBuffer()
	{
		if (_vbo_count != 0)
		{
			glDeleteBuffers(_vbo_count, _vbo.get());
		}
	}

	void KiteDriverMeshDrawer::Render(KiteDriverMaterial* material)
	{
		material->BeginRender();
		{
			DrawMesh();
		}
		material->EndRender();
	}

	GLuint KiteDriverMeshDrawer::GetUVAttribIndex(int uv_index)
	{
		return 2 + uv_index;
	}

}