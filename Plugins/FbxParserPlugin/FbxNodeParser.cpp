#include "stdafx.h"
#include "FbxNodeParser.h"
#include "fbxsdk.h"

namespace kite_fbx
{
	FbxNodeParser::FbxNodeParser()
	{
	}


	FbxNodeParser::~FbxNodeParser()
	{
	}

	void FbxNodeParser::Parse(FbxScene * scene)
	{
		FbxNode* lNode = scene->GetRootNode();

		if (lNode)
		{
			for (int i = 0; i < lNode->GetChildCount(); i++)
			{
				ParseNode(lNode->GetChild(i));
			}
		}
	}

	void FbxNodeParser::ParseNode(FbxNode * node)
	{
		if (node->GetNodeAttribute() == NULL)
		{
			FBXSDK_printf("NULL Node Attribute\n\n");
		}
		else
		{
			auto lAttributeType = (node->GetNodeAttribute()->GetAttributeType());

			switch (lAttributeType)
			{
			case FbxNodeAttribute::eMesh:
			{
				auto mesh = std::make_shared<FbxMeshParser>();
				mesh->Parse(node);
				_meshes.push_back(mesh);
			}

			break;
			}
		}
	}
}