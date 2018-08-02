#pragma once

namespace kite_driver
{
	class KiteDriverCamera : public KiteDriverDummy
	{
	public:
		KiteDriverCamera();
		~KiteDriverCamera();

		void set_fovy(float fovy);
		void set_aspect(float aspect);
		void set_near_plane(float near_plane);
		void set_far_plane(float far_plane);

		const kite_math::Matrix4f& get_perspective_matrix() { return _perspective_matrix; }
		const kite_math::Matrix4f& get_view_matrix() { return _view_matrix; }

		const kite_math::Matrix4f& get_skybox_vp_matrix() { return _skybox_vp_matrix; }

		void SetCameraMatrices(KiteDriverRenderObject* render_object);
		void SetCameraMatrices(KiteDriverRenderObject* render_object, KiteDriverMaterial* material);

		void set_view_port(const ViewPort& view_port) { _view_port = view_port; }
		const ViewPort& get_view_port() const{ return _view_port; }
	protected: 
		void RefreshProjectMatrix();
		virtual void RefreshWorldMatrix() override;

		void RefreshVPMatrix();
	private:
		float _fovy;
		float _aspect;
		float _near_plane;
		float _far_plane;

		kite_math::Matrix4f _view_matrix;
		kite_math::Matrix4f _perspective_matrix;
		kite_math::Matrix4f _skybox_perspective_matrix;

		kite_math::Matrix4f _skybox_vp_matrix;

		ViewPort _view_port;
	};

	typedef std::shared_ptr<KiteDriverCamera> KiteDriverCameraPtr;
}
