// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <algorithm>
#include <map>

#include "glew.h"


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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