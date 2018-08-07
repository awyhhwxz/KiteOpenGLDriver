#include "stdafx.h"
#include "KiteDriverCamera.h"

namespace kite_driver
{
	KiteDriverCamera::KiteDriverCamera()
		: KiteDriverDummy(),
		_fovy(kite_math::Mathf::PI / 3.0f),
		_aspect(1),
		_far_plane(1000),
		_near_plane(0.5)
	{
		RefreshProjectMatrix();
		RefreshWorldMatrix();
	}


	KiteDriverCamera::~KiteDriverCamera()
	{
	}

	kite_driver::KiteDriverObjectType KiteDriverCamera::get_type()
	{
		return KiteDriverObjectType::KDOT_CAMERA;
	}

	void KiteDriverCamera::set_fovy(float fovy)
	{
		_fovy = fovy; 
		RefreshProjectMatrix();
	}

	kite_math::Ray KiteDriverCamera::GenerateRayFromScreenPos(const kite_math::Vector2f & screen_pos)
	{
		auto near_point = UnProjectToWorldPos(kite_math::Vector3f(screen_pos, _near_plane));
		auto far_point = UnProjectToWorldPos(kite_math::Vector3f(screen_pos, _far_plane));
		auto dircect = far_point - near_point;
		return kite_math::Ray(near_point, kite_math::Vector3f::Normalize(dircect), kite_math::Vector3f::Distance(dircect));
	}

	kite_math::Vector3f KiteDriverCamera::UnProjectToWorldPos(const kite_math::Vector3f & screen_pos)
	{
		kite_math::Vector3f normal_viewport;
		normal_viewport.x = kite_math::Mathf::ZeroOneToPNOne((screen_pos.x - _view_port.get_x()) / _view_port.get_width());
		normal_viewport.y = -kite_math::Mathf::ZeroOneToPNOne((screen_pos.y - _view_port.get_y()) / _view_port.get_height());
		normal_viewport.z = 0.95f;

		auto virtual_world_pos = _inverse_view_matrix * _inverse_perspective_matrix * normal_viewport;
		auto virtual_vector = virtual_world_pos - _pos;
		auto forward_vector = _world.GetZAxis();
		auto virtual_z_length = kite_math::Vector3f::Dot(virtual_vector, forward_vector);
		
		kite_math::Vector3f result_vector;
		if (kite_math::Mathf::Abs(virtual_z_length) < kite_math::Mathf::kFloatPrecision)
		{
			result_vector = virtual_world_pos;
		}
		else
		{
			result_vector = _pos + virtual_vector * (screen_pos.z / virtual_z_length);
		}

		return result_vector;
	}

	void KiteDriverCamera::RefreshProjectMatrix()
	{
		_perspective_matrix = kite_math::Matrix4f::PerspectiveRHand(_fovy, _aspect, _near_plane, _far_plane);
		_inverse_perspective_matrix = kite_math::Matrix4f::Inverse(_perspective_matrix);
		_skybox_perspective_matrix = kite_math::Matrix4f::PerspectiveRHand(_fovy, _aspect, 0.1f, 100.0f);

		RefreshVPMatrix();
	}

	void KiteDriverCamera::RefreshWorldMatrix()
	{
		KiteDriverDummy::RefreshWorldMatrix();
		kite_math::Matrix4f trans_m;
		trans_m._11 = 1; trans_m._22 = 1; trans_m._33 = -1; trans_m._44 = 1;
		_view_matrix = trans_m * _inverse_world;
		_inverse_view_matrix = kite_math::Matrix4f::Inverse(_view_matrix);

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