#pragma once

namespace kite_driver
{
	class KiteDriverTextureBlurDrawer
	{
	public:
		KiteDriverTextureBlurDrawer();
		~KiteDriverTextureBlurDrawer();

		void Blur(const KiteDriverRenderTexturePtr& src, const KiteDriverFrameBufferPtr& dest);

		void set_blur_iter_num(int blur_iter_num) { _blur_iter_num = blur_iter_num; }
		void set_blur_point_size(float blur_point_size);
		void set_blur_texel_size(float blur_texel_size);

	private:
		void SetPointSize(float point_size);

	private:
		int _blur_iter_num;
		float _blur_point_size;
		float _blur_texel_size;

		KiteDriverMaterialPtr _vertical_blur_mat;
		KiteDriverMaterialPtr _horizontal_blur_mat;

		KiteDriverRenderTexturePtr _temp_rt_1;
		KiteDriverRenderTexturePtr _temp_rt_2;
		KiteDriverFrameBufferPtr _temp_frame_buffer;
	};

}