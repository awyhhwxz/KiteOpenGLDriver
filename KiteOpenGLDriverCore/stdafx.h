// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <algorithm>
#include <map>

#include "glew.h"


// TODO:  在此处引用程序需要的其他头文件
#include "KiteOpenGLDriverCoreLib.h"
#include "KiteUtilLib.h"
#include "KiteDriverParaValueType.h"
#include "KiteDriverParaValue.h"
#include "KiteDriverShaderVisitor.h"
#include "KiteDriverTexture2D.h"
#include "KiteDriverTextureCube.h"
#include "KiteDriverProgramBuilder.h"
#include "KiteDriverEnumOpenGLEnumConverter.h"
#include "KiteDriverMesh.h"
#include "KiteDriverMeshDrawer.h"
#include "KiteDriverRenderStateSetter.h"
#include "KiteDriverMaterial.h"
#include "KiteDriverDummy.h"
#include "KiteDriverRenderObject.h"
#include "KiteDriverCamera.h"
#include "KiteDriverSkyBox.h"
#include "KiteDriverScene.h"

#include "KiteDriverInputManager.h"
#include "KiteDriverWindowManager.h"