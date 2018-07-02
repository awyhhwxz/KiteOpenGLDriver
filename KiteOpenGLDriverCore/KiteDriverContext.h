#pragma once

namespace kite_driver
{

	class KiteDriverContext : public IKiteDriverContext
	{
	public:
		KiteDriverContext();
		~KiteDriverContext();

		virtual void Initialize(void* hwnd) override;
		virtual void AddRenderItem(IKiteDriverRenderItem* render_item) override;
		virtual void RemeveRenderItem(IKiteDriverRenderItem* render_item) override;
		virtual void Render() override;

	protected:
		void OnInitialize();

	protected:
		HWND _hwnd;
		std::vector<IKiteDriverRenderItem*> _render_items;
		std::vector<IKiteDriverRenderItem*> _uninitialized_items;
		bool _is_init;
	};
}

