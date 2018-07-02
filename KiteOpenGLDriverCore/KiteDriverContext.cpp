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

	void KiteDriverContext::Initialize(void* hwnd)
	{

		// remember the window handle (HWND)
		_hwnd = (HWND)hwnd;

		HDC mhDC;
		HGLRC mhRC;
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
		mhRC = wglCreateContext(mhDC);

		// make it the current render context
		wglMakeCurrent(mhDC, mhRC);


		glewInit();
		OnInitialize();
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
		glClearColor(0.5f, 0.5f, 0.5f, 1.f);
		glClearDepth(1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		std::for_each(_render_items.begin(), _render_items.end(), [](IKiteDriverRenderItem* render_item)
		{
			glLoadIdentity();
			render_item->Render();
		});

		//glFlush();
		auto dc = GetDC(_hwnd);
		SwapBuffers(dc);
		ReleaseDC(_hwnd, dc);
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