#include "stdafx.h"
#include "KiteDriverMeshDrawer.h"

namespace kite_driver
{
	KiteDriverMeshDrawer::KiteDriverMeshDrawer()
	{
	}


	KiteDriverMeshDrawer::~KiteDriverMeshDrawer()
	{
		glDeleteBuffers(2, _vbo.get());
	}

	void kite_driver::KiteDriverMeshDrawer::BindData()
	{
		int vbo_count = 2 + _mesh->GetUVChannelCount();
		_vbo.reset(new GLuint[vbo_count]);
		auto vboPointer = _vbo.get();
		glGenBuffers(vbo_count, vboPointer);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		auto vert = _mesh->GetVertices();
		auto verticesSize = _mesh->GetVertexCount() * sizeof(kite_math::Vector3f);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vert, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
		auto inde = _mesh->GetIndices();
		auto indicesSize = _mesh->GetIndexCount() * sizeof(uint16);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, inde, GL_STATIC_DRAW);

		for (int uvi = 0 ; uvi < _mesh->GetUVChannelCount() ; ++uvi)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[2 + uvi]);
			auto uvs = _mesh->GetUVs(uvi);
			auto uvsSize = _mesh->GetVertexCount() * sizeof(kite_math::Vector2f);
			glBufferData(GL_ARRAY_BUFFER, uvsSize, uvs, GL_STATIC_DRAW);
		}
	}
	void KiteDriverMeshDrawer::DrawMesh()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		for (int uvi = 0; uvi < _mesh->GetUVChannelCount(); ++uvi)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[2 + uvi]);

			GLuint uv_attrib_index = GetUVAttribIndex(uvi);
			glVertexAttribPointer(uv_attrib_index, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(uv_attrib_index + uvi);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);

		glDrawElements(GL_TRIANGLES, _mesh->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		glDisableVertexAttribArray(0);
		for (int uvi = 0; uvi < _mesh->GetUVChannelCount(); ++uvi)
		{
			glDisableVertexAttribArray(GetUVAttribIndex(uvi));
		}
	}

	GLuint KiteDriverMeshDrawer::GetUVAttribIndex(int uv_index)
	{
		return 1 + uv_index;
	}

}