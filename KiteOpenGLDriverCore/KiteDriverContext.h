#pragma once

namespace kite_driver
{

	class KiteDriverContext : public IKiteDriverContext
	{
	public:
		KiteDriverContext();
		~KiteDriverContext();

		virtual void Initialize(void* hwnd, float width, float height) override;
		virtual void Finalize();
		virtual void AddRenderItem(IKiteDriverRenderItem* render_item) override;
		virtual void RemeveRenderItem(IKiteDriverRenderItem* render_item) override;
		virtual void Render() override;
		virtual void Resize(int width, int height) override;

	protected:
		void OnInitialize();

	protected:
		HWND _hwnd;
		HGLRC _rc;

		std::vector<IKiteDriverRenderItem*> _render_items;
		std::vector<IKiteDriverRenderItem*> _uninitialized_items;
		bool _is_init;
	};
}

