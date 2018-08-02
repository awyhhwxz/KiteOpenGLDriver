#pragma once

#include "KiteDriverTextureBlurDrawer.h"

namespace kite_driver
{
	class KiteDriverHighLightingManager : public Singleton<KiteDriverHighLightingManager>
	{
	public:
		KiteDriverHighLightingManager();
		~KiteDriverHighLightingManager();

		void AddHighLightingObj(KiteDriverRenderObjectPtr highlighting_obj);
		void RemoveHighLightingObj(KiteDriverRenderObjectPtr highlighting_obj);

		void Clear();

		void RenderHighLighting(KiteDriverCamera* camera);

		const KiteDriverRenderTexturePtr& GetHighLightTexture();

	private:
		std::vector<std::weak_ptr<KiteDriverRenderObject> > _highlight_obj_list;
		KiteDriverRenderTexturePtr _render_texture;
		KiteDriverMaterialPtr _pure_color_material;
		KiteDriverMaterialPtr _substraction_material;
		KiteDriverTextureBlurDrawer _blur_drawer;
	};
}
