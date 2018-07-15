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
		_vbo.reset(new GLuint[2]);
		auto vboPointer = _vbo.get();
		glGenBuffers(2, vboPointer);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		auto vert = _mesh->GetVertices();
		auto verticesSize = _mesh->GetVertexCount() * sizeof(kite_math::Vector3f);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vert, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
		auto inde = _mesh->GetIndices();
		auto indicesSize = _mesh->GetIndexCount() * sizeof(uint16);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, inde, GL_STATIC_DRAW);
	}
	void KiteDriverMeshDrawer::DrawMesh()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);

		glDrawElements(GL_TRIANGLES, _mesh->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		glDisableVertexAttribArray(0);
	}
}