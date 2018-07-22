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

}