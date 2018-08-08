#include "stdafx.h"
#include "WindowsHelper.h"


WindowsHelper::WindowsHelper()
{
}


WindowsHelper::~WindowsHelper()
{
}

SIZE WindowsHelper::GetClientWindowSize(HWND hwnd)
{
	RECT clientRect;
	::GetClientRect(hwnd, &clientRect);
	SIZE size;
	size.cx = clientRect.right - clientRect.left;
	size.cy = clientRect.bottom - clientRect.top;
	return size;
}
