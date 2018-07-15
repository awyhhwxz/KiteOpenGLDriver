#pragma once
class WindowsMouseMessageHandler
{
public:
	WindowsMouseMessageHandler();
	~WindowsMouseMessageHandler();

public: 
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

private:
	kite_driver::MouseButtonType GetMouseButtonType(UINT message);
	kite_math::Vector2f GetMousePosition(LPARAM lParam);
};

