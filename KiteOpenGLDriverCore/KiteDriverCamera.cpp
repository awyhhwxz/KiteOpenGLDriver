#include "stdafx.h"
#include "KiteDriverCamera.h"

namespace kite_driver
{
	KiteDriverCamera::KiteDriverCamera()
		: KiteDriverDummy(),
		_fovy(kite_math::Mathf::PI / 3.0f),
		_aspect(1),
		_far_plane(1000),
		_near_plane(0.01)
	{
		RefreshProjectMatrix();
		RefreshWorldMatrix();
	}


	KiteDriverCamera::~KiteDriverCamera()
	{
	}

	void KiteDriverCamera::set_fovy(float fovy)
	{
		_fovy = fovy; 
		RefreshProjectMatrix();
	}

	void KiteDriverCamera::RefreshProjectMatrix()
	{
		_perspective_matrix = kite_math::Matrix4f::PerspectiveRHand(_fovy, _aspect, _near_plane, _far_plane);
		_skybox_perspective_matrix = kite_math::Matrix4f::PerspectiveRHand(_fovy, _aspect, _near_plane, _far_plane);

		RefreshVPMatrix();
	}

	void KiteDriverCamera::RefreshWorldMatrix()
	{
		KiteDriverDummy::RefreshWorldMatrix();
		kite_math::Matrix4f trans_m;
		trans_m._11 = 1; trans_m._22 = 1; trans_m._33 = -1; trans_m._44 = 1;
		_view_matrix = trans_m * _inverse_world;

		RefreshVPMatrix();
	}

	void KiteDriverCamera::RefreshVPMatrix()
	{
		kite_math::Matrix4f trans_m;
		trans_m._11 = 1; trans_m._22 = 1; trans_m._33 = -1; trans_m._44 = 1;
		_skybox_vp_matrix = _skybox_perspective_matrix * trans_m * kite_math::Matrix4f::Transpose(kite_math::Matrix4f::Rotate(_euler));
	}

	void KiteDriverCamera::set_aspect(float aspect)
	{
		_aspect = aspect; 
		RefreshProjectMatrix();
	}

	void KiteDriverCamera::set_near_plane(float near_plane)
	{
		_near_plane = near_plane;
		RefreshProjectMatrix();
	}

	void KiteDriverCamera::set_far_plane(float far_plane)
	{
		_far_plane = far_plane; 
		RefreshProjectMatrix();
	}

	void KiteDriverCamera::SetCameraMatrices(KiteDriverRenderObject* render_object)
	{
		auto material = render_object->get_material();
		if (material != nullptr)
		{
			SetCameraMatrices(render_object, material);
		}
	}

	void KiteDriverCamera::SetCameraMatrices(KiteDriverRenderObject* render_object, KiteDriverMaterial* material)
	{
		auto model_matrix = render_object->get_world_matrix();
		material->SetUniformValue("model_matrix", KDPVT_MATRIX4F, model_matrix.values);
		auto view_matrix = this->get_view_matrix();
		auto mv_matrix = view_matrix * model_matrix;
		material->SetUniformValue("mv", KDPVT_MATRIX4F, mv_matrix.values);
		auto perspective_matrix = this->get_perspective_matrix();
		auto mvp_matrix = perspective_matrix * mv_matrix;
		material->SetUniformValue("mvp", KDPVT_MATRIX4F, mvp_matrix.values);

	}

}