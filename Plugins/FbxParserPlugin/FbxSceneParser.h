#pragma once

namespace kite_fbx
{
	class KITE_FBX_API FbxSceneParser
	{
	public:
		FbxSceneParser();
		~FbxSceneParser();

		bool LoadScene(const char* fbx_path);

		FbxScene* get_scene() { return _fbx_scene; }
	protected:
		void Initialize();
		void Finalize();

	private:
		FbxManager * _fbx_manager;
		FbxScene* _fbx_scene;
	};

	typedef std::shared_ptr<FbxSceneParser> FbxSceneParserPtr;
}