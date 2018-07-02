#pragma once

#ifdef KITEMATH_EXPORTS
#define KITE_MATH_API __declspec(dllexport)
#else
#define KITE_MATH_API __declspec(dllimport)
#endif

#include "Vector3f.h"