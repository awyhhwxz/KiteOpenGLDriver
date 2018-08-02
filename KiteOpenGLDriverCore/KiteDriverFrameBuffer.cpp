#include "stdafx.h"
#include "KiteDriverFrameBuffer.h"


namespace kite_driver
{
	KiteDriverFrameBuffer::KiteDriverFrameBuffer()
		: _fbo(0), _depth_id(0), _fbo_is_init(false)
	{

	}


	KiteDriverFrameBuffer::~KiteDriverFrameBuffer()
	{
		if(_fbo > 0) glDeleteFramebuffers(1, &_fbo);
		if(_depth_id > 0) glDeleteRenderbuffers(1, &_depth_id);
	}
	
	void KiteDriverFrameBuffer::GenerateFBO()
	{
		if (!_fbo_is_init)
		{
			glGenFramebuffers(1, &_fbo);
			glGenRenderbuffers(1, &_depth_id);
			_fbo_is_init = true;
		}
	}
		
	void KiteDriverFrameBuffer::BeginRender()
	{
		if (_render_target)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			KiteDriverGraphics::SetViewPort(ViewPort(0, 0, _render_target->get_width(), _render_target->get_height()));
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			KiteDriverGraphics::SetViewPort(_view_port);
		}
	}

	void KiteDriverFrameBuffer::EndRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void KiteDriverFrameBuffer::SetRenderTarget(const KiteDriverRenderTexturePtr & render_target)
	{
		if (_render_target != render_target)
		{
			_render_target = render_target;
			if (_render_target)
			{
				GenerateFBO();

				glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

				glBindRenderbuffer(GL_RENDERBUFFER, _depth_id);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, render_target->get_width(), render_target->get_height());
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth_id);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				auto tex_id = render_target->get_gl_tex_id();
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_id, 0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
	}

	const KiteDriverRenderTexturePtr&  KiteDriverFrameBuffer::GetRenderTarget()
	{
		return _render_target;
	}

}