#pragma once


namespace kite_fbx
{
	class KITE_FBX_API FbxNodeParser : public IFbxNode
	{
	public:
		FbxNodeParser();
		~FbxNodeParser();

		void Parse(FbxScene* scene);

		virtual const std::vector<IFbxMeshPtr>& get_meshes() override { return _meshes; }
	protected:
		void ParseNode(FbxNode* node);

	private:
		std::vector<IFbxMeshPtr> _meshes;
	};

	typedef std::shared_ptr<FbxNodeParser> FbxNodeParserPtr;
}