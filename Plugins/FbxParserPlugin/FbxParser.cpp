#include "stdafx.h"
#include "FbxParser.h"

namespace kite_fbx
{
	FbxParser::FbxParser()
	{
	}


	FbxParser::~FbxParser()
	{
	}

	IFbxNodePtr FbxParser::LoadFbx(const char* fbx_path)
	{
		FbxSceneParser scene_parser;
		scene_parser.LoadScene(fbx_path);
		auto scene = scene_parser.get_scene();
		FbxNodeParserPtr node_parser = std::make_shared<FbxNodeParser>();
		node_parser->Parse(scene);
		return node_parser;
	}

}