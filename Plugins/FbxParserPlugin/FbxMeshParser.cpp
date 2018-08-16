#include "stdafx.h"
#include "FbxMeshParser.h"

namespace kite_fbx
{
	FbxMeshParser::FbxMeshParser()
	{

	}


	FbxMeshParser::~FbxMeshParser()
	{
	}

	void FbxMeshParser::Parse(FbxNode* node)
	{
		_name = node->GetName();
		FbxMesh* mesh = (FbxMesh*)node->GetNodeAttribute();
		
		auto polygon_count = mesh->GetPolygonCount();
		_polygon_size = mesh->GetPolygonSize(0);
		_faces.clear();
		_faces.resize(polygon_count);

		int current_index = 0;
		for (int polygon_i = 0; polygon_i < polygon_count; polygon_i++)
		{
			int polygon_size = mesh->GetPolygonSize(polygon_i);

			FbxMeshData& face = _faces[polygon_i];
			face.Count = polygon_size;
			for (int polygon_size_i = 0; polygon_size_i < polygon_size; polygon_size_i++)
			{
				auto controlpoint_i = mesh->GetPolygonVertex(polygon_i, polygon_size_i);
				ParseVertex(mesh, controlpoint_i, &face);
				ParseNormal(mesh, current_index, &face);
				ParseUV(mesh, polygon_i, polygon_size_i, &face);
				++current_index;
			}
		}

		RefreshData();

	}

	void FbxMeshParser::RefreshData()
	{
		int current_index = 0;
		std::for_each(_faces.begin(), _faces.end(), [this, &current_index](auto& face)
		{
			_data.Append(&face);

			switch (face.Count)
			{
			case 3:
				for (int polygon_i = 0; polygon_i < _polygon_size; ++polygon_i)
				{
					_indexes.push_back(current_index + polygon_i);
				}
				break;
			case 4:
				_indexes.push_back(current_index);
				_indexes.push_back(current_index + 1);
				_indexes.push_back(current_index + 2);
				_indexes.push_back(current_index);
				_indexes.push_back(current_index + 2);
				_indexes.push_back(current_index + 3);
				break;
			}
			current_index += _polygon_size;
		});

		_data.ResetCount();
	}

	void FbxMeshParser::ParseVertex(FbxMesh * mesh, int controlpoint_i, FbxMeshData* face)
	{
		auto controlpoint = mesh->GetControlPointAt(controlpoint_i);
		face->Vertices.push_back(kite_math::Vector3f(controlpoint[0], controlpoint[1], controlpoint[2]));
	}

	void FbxMeshParser::ParseNormal(FbxMesh* mesh, int current_index, FbxMeshData* face)
	{
		auto normal_count = mesh->GetElementNormalCount();
		for (int normal_i = 0; normal_i < normal_count; ++normal_i)
		{
			FbxVector4 normal_val;
			FbxGeometryElementNormal* normal = mesh->GetElementNormal(normal_i);
			switch (normal->GetMappingMode())
			{
			case FbxGeometryElement::eByPolygonVertex:
				switch (normal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					normal_val = normal->GetDirectArray().GetAt(current_index);
					break;
				case FbxGeometryElement::eIndexToDirect:
				{
					int id = normal->GetIndexArray().GetAt(current_index);
					normal_val = normal->GetDirectArray().GetAt(id);
				}
					break;
				}
				break;
			}

			face->Normals[normal_i].push_back(kite_math::Vector3f(normal_val[0], normal_val[1], normal_val[2]));
		}
	}

	void FbxMeshParser::ParseUV(FbxMesh * mesh, int polygon_i, int polygon_size_i, FbxMeshData * face)
	{
		auto uv_count = mesh->GetElementUVCount();
		for (int uv_i = 0 ; uv_i < uv_count ; ++uv_i)
		{
			FbxGeometryElementUV* uv = mesh->GetElementUV(uv_i);
			FbxVector2 uv_val;
			switch (uv->GetMappingMode())
			{
			case FbxGeometryElement::eByControlPoint:
			{
				auto controlpoint_i = mesh->GetPolygonVertex(polygon_i, polygon_size_i);
				switch (uv->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					uv_val = uv->GetDirectArray().GetAt(controlpoint_i);
					break;
				case FbxGeometryElement::eIndexToDirect:
				{
					int id = uv->GetIndexArray().GetAt(controlpoint_i);
					uv_val = uv->GetDirectArray().GetAt(id);
				}
				break;
				}
				break;
			}
			case FbxGeometryElement::eByPolygonVertex:
			{
				int texture_uv_index = mesh->GetTextureUVIndex(polygon_i, polygon_size_i);
				switch (uv->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				case FbxGeometryElement::eIndexToDirect:
				{
					uv_val = uv->GetDirectArray().GetAt(texture_uv_index);
				}
				break;
				}
			}
			break;
			}

			face->UVs[uv_i].push_back(kite_math::Vector2f(uv_val[0], uv_val[1]));
		}
	}

}