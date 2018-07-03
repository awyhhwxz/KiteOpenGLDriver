// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <memory>

#include "glew.h"
#include <gl/gl.h>
#include <gl/glu.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "KiteMathLib.h"
#include "KiteUtilLib.h"
#include "KiteOpenGLDriverCoreLib.h"
#include "KiteDriverShaderVisitor.h"
#include "KiteDriverProgramBuilder.h"
#include "KiteDriverEnumOpenGLEnumConverter.h"
#include "KiteDriverMesh.h"
#include "KiteDriverMaterial.h"