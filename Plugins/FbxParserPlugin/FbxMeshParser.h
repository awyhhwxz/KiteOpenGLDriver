#pragma once

namespace kite_fbx
{
	class KITE_FBX_API FbxMeshParser : public IFbxMesh
	{
	public:
		FbxMeshParser();
		~FbxMeshParser();

	public:
		void Parse(FbxNode* node);

		virtual const FbxMeshData& get_mesh_data() override { return _data; }
		virtual const std::vector<unsigned short>& get_indexes() override { return _indexes; }

	private:
		void RefreshData();
	private:
		void ParseVertex(FbxMesh* mesh, int controlpoint_i, FbxMeshData* face);
		void ParseNormal(FbxMesh* mesh, int current_index, FbxMeshData* face);
		void ParseUV(FbxMesh* mesh, int polygon_i, int polygon_size_i, FbxMeshData* face);
	private:
		std::vector<FbxMeshData> _faces;
		FbxMeshData _data;
		std::vector<unsigned short> _indexes;
		int _polygon_size;
		std::string _name;
	};

	typedef std::shared_ptr<FbxMeshParser> FbxMeshParserPtr;
}