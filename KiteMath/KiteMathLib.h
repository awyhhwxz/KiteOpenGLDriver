#pragma once

#ifdef KITEMATH_EXPORTS
#define KITE_MATH_API __declspec(dllexport)
#else
#define KITE_MATH_API __declspec(dllimport)
#endif

#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix4f.h"