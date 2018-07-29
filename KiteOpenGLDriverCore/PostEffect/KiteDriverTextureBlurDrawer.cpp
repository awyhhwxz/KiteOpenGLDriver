#include "stdafx.h"
#include "KiteDriverTextureBlurDrawer.h"
#include "KiteDriverFastAccess.h"

namespace kite_driver
{
	KiteDriverTextureBlurDrawer::KiteDriverTextureBlurDrawer()
		: _blur_iter_num(4)
		, _blur_point_size(1.0f)
		, _blur_texel_size(0.001f)
	{
		auto resource_path = kite_util::PathUtil::GetResourcePath();

		_vertical_blur_mat = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture_blur_vertical.vertex",
			"/shader/texture_blur.fragment"
			);
		_vertical_blur_mat->Link();

		_horizontal_blur_mat = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture_blur_horizontal.vertex",
			"/shader/texture_blur.fragment"
		);
		_horizontal_blur_mat->Link();

		_temp_rt_1 = std::make_shared<KiteDriverRenderTexture>();
		_temp_rt_2 = std::make_shared<KiteDriverRenderTexture>();

		_temp_frame_buffer = std::make_shared<KiteDriverFrameBuffer>();

		set_blur_texel_size(_blur_texel_size);
	}


	KiteDriverTextureBlurDrawer::~KiteDriverTextureBlurDrawer()
	{
	}

	void KiteDriverTextureBlurDrawer::Blur(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest)
	{
		auto temp_rt_1 = src;
		auto temp_rt_2 = _temp_rt_2;
		for (int iter_i = 0 ; iter_i < _blur_iter_num ; ++iter_i)
		{
			SetPointSize(1.0f + _blur_point_size * iter_i);

			_horizontal_blur_mat->SetUniformTexture("tex", temp_rt_1);
			_temp_frame_buffer->SetRenderTarget(temp_rt_2);
			KiteDriverGraphics::Blit(temp_rt_1, _temp_frame_buffer.get(), _horizontal_blur_mat);
			temp_rt_1 = _temp_rt_1;

			_vertical_blur_mat->SetUniformTexture("tex", temp_rt_2);
			_temp_frame_buffer->SetRenderTarget(temp_rt_1);
			KiteDriverGraphics::Blit(temp_rt_2, _temp_frame_buffer.get(), _vertical_blur_mat);
			temp_rt_2 = _temp_rt_2;
		}

		KiteDriverGraphics::Blit(temp_rt_1, dest.get());
	}

	void KiteDriverTextureBlurDrawer::set_blur_point_size(float blur_point_size)
	{
		_blur_point_size = blur_point_size;
	}

	void KiteDriverTextureBlurDrawer::set_blur_texel_size(float blur_texel_size)
	{
		_blur_texel_size = blur_texel_size;
		_horizontal_blur_mat->SetUniformValue("_TexelSize", KiteDriverParaValueType::KDPVT_FLOAT, &_blur_texel_size);
		_vertical_blur_mat->SetUniformValue("_TexelSize", KiteDriverParaValueType::KDPVT_FLOAT, &_blur_texel_size);
	}

	void KiteDriverTextureBlurDrawer::SetPointSize(float blur_point_size)
	{
		_horizontal_blur_mat->SetUniformValue("_PointSize", KiteDriverParaValueType::KDPVT_FLOAT, &blur_point_size);
		_vertical_blur_mat->SetUniformValue("_PointSize", KiteDriverParaValueType::KDPVT_FLOAT, &blur_point_size);
	}

}