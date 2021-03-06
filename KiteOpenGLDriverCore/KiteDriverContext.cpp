#include "stdafx.h"
#include "KiteDriverContext.h"


namespace kite_driver
{
	KiteDriverContext::KiteDriverContext()
	{
	}


	KiteDriverContext::~KiteDriverContext()
	{
	}

	void KiteDriverContext::Initialize(void* hwnd, float width, float height)
	{
		// remember the window handle (HWND)
		_hwnd = (HWND)hwnd;

		HDC mhDC;
		// get the device context (DC)
		mhDC = GetDC(_hwnd);

		// set the pixel format for the DC
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;
		int format = ChoosePixelFormat(mhDC, &pfd);
		SetPixelFormat(mhDC, format, &pfd);

		// create the render context (RC)
		_rc = wglCreateContext(mhDC);

		// make it the current render context
		wglMakeCurrent(mhDC, _rc);
		ReleaseDC(_hwnd, mhDC);

		glewInit();
		KiteDriverWindowManager::Instance()->SetWindowWidthAndHeight(width, height);
		OnInitialize();
	}

	void KiteDriverContext::Finalize()
	{
		wglDeleteContext(_rc);
	}

	void KiteDriverContext::AddRenderItem(IKiteDriverRenderItem * render_item)
	{
		_render_items.push_back(render_item);
		if (_is_init)
		{
			render_item->Initialize();
		}
		else
		{
			_uninitialized_items.push_back(render_item);
		}
	}

	void KiteDriverContext::RemeveRenderItem(IKiteDriverRenderItem * render_item)
	{
		auto found_iter = std::find(_render_items.begin(), _render_items.end(), render_item);
		if (found_iter != _render_items.end())
		{
			_render_items.erase(found_iter);
		}
	}

	void KiteDriverContext::Render()
	{
		std::for_each(_render_items.begin(), _render_items.end(), [](IKiteDriverRenderItem* render_item)
		{
			glLoadIdentity();
			render_item->Render();
		});

		glFlush();
		auto dc = GetDC(_hwnd);
		SwapBuffers(dc);
		ReleaseDC(_hwnd, dc);
	}

	void KiteDriverContext::Resize(int width, int height)
	{
		glViewport(0, 0, width, height);
		KiteDriverWindowManager::Instance()->SetWindowWidthAndHeight(width, height);
	}

	void KiteDriverContext::OnInitialize()
	{
		_is_init = true;
		std::for_each(_uninitialized_items.begin(), _uninitialized_items.end(), [](IKiteDriverRenderItem* render_item)
		{
			render_item->Initialize();
		});
	}

}