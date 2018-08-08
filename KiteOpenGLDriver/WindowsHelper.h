#pragma once
class WindowsHelper
{
public:
	WindowsHelper();
	~WindowsHelper();

	static SIZE GetClientWindowSize(HWND hwnd);
};

