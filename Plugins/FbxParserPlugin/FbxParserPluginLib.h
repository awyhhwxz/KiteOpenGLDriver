#pragma once

#ifdef FBXPARSERPLUGIN_EXPORTS
#define KITE_FBX_API __declspec(dllexport)
#else
#define KITE_FBX_API __declspec(dllimport)
#endif

#include "KiteMathLib.h"

#include "FbxMeshData.h"
#include "IFbxMesh.h"
#include "IFbxNode.h"

#include "FbxParser.h"