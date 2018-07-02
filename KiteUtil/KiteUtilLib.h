#pragma once

#ifdef KITEUTIL_EXPORTS
#define KITE_UTIL_API __declspec(dllexport)
#else
#define KITE_UTIL_API __declspec(dllimport)
#endif



#include "StringReader.h"
#include "PathUtil.h"