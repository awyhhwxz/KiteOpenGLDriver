#include "stdafx.h"
#include "WindowsMouseMessageHandler.h"


WindowsMouseMessageHandler::WindowsMouseMessageHandler()
{
}


WindowsMouseMessageHandler::~WindowsMouseMessageHandler()
{
}

void WindowsMouseMessageHandler::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		kite_driver::KiteDriverInputManager::Instance()->InvokeMouseMove(GetMousePosition(lParam));
	}
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		kite_driver::KiteDriverInputManager::Instance()->InvokeButtonDown(GetMouseButtonType(message), GetMousePosition(lParam));
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		kite_driver::KiteDriverInputManager::Instance()->InvokeButtonUp(GetMouseButtonType(message), GetMousePosition(lParam));
		break;
	case WM_MOUSEWHEEL:
		kite_driver::KiteDriverInputManager::Instance()->OnMouseWheelRoll((INT)wParam);
		break;
	default:
		break;
	}
}

kite_driver::MouseButtonType WindowsMouseMessageHandler::GetMouseButtonType(UINT message)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		return kite_driver::MouseButtonType::MBT_LEFT;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		return kite_driver::MouseButtonType::MBT_RIGHT;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		return kite_driver::MouseButtonType::MBT_MIDDLE;
	default:
		break;
	}

	return kite_driver::MouseButtonType();
}

kite_math::Vector2f WindowsMouseMessageHandler::GetMousePosition(LPARAM lParam)
{
	auto x = LOWORD(lParam);
	auto y = HIWORD(lParam);
	return kite_math::Vector2f(x, y);
}
