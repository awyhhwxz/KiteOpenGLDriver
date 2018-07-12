// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>

#include "glew.h"
#include <gl/gl.h>
#include <gl/glu.h>

// TODO:  在此处引用程序需要的其他头文件
#include "KiteMathLib.h"
#include "KiteUtilLib.h"
#include "KiteOpenGLDriverCoreLib.h"
#include "KiteDriverParaValueType.h"
#include "KiteDriverParaValue.h"
#include "KiteDriverShaderVisitor.h"
#include "KiteDriverProgramBuilder.h"
#include "KiteDriverEnumOpenGLEnumConverter.h"
#include "KiteDriverMesh.h"
#include "KiteDriverMeshDrawer.h"
#include "KiteDriverMaterial.h"
#include "KiteDriverDummy.h"
#include "KiteDriverRenderObject.h"
#include "KiteDriverCamera.h"
#include "KiteDriverScene.h"