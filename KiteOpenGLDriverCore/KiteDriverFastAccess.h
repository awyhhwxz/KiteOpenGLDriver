#pragma once
namespace kite_driver
{
	class KiteDriverFastAccess
	{
	public:
		static KiteDriverMaterialPtr GenerateMaterialByShader(const tchar* vertex_shader_path, const tchar* fragment_shader_path);

		static KiteDriverTexture2DPtr GenerateTexture2D(const tchar* image_path);

		static KiteDriverMeshPtr LoadFbxMesh(const tchar* fbx_path);
	};
}
