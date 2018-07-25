#include "stdafx.h"
#include "KiteDriverFrameBuffer.h"


namespace kite_driver
{
	KiteDriverFrameBuffer::KiteDriverFrameBuffer()
		: _fbo(0)
	{
		glGenFramebuffers(1, &_fbo);
		glGenRenderbuffers(1, &_depth_id);
	}


	KiteDriverFrameBuffer::~KiteDriverFrameBuffer()
	{
		glDeleteFramebuffers(1, &_fbo);
		glDeleteRenderbuffers(1, &_depth_id);
	}

	void KiteDriverFrameBuffer::BeginRender(KiteDriverCamera* camera)
	{
		if (_render_target)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glViewport(0, 0, _render_target->get_width(), _render_target->get_height());
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, KiteDriverWindowManager::Instance()->get_window_width(), KiteDriverWindowManager::Instance()->get_window_height());
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
}