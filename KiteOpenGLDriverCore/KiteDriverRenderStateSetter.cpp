#include "stdafx.h"
#include "KiteDriverRenderStateSetter.h"


namespace kite_driver
{
	KiteDriverRenderStateSetter::KiteDriverRenderStateSetter()
		: _enable_zwrite(true)
	{
	}


	KiteDriverRenderStateSetter::~KiteDriverRenderStateSetter()
	{
	}
	void KiteDriverRenderStateSetter::SetZWriteEnable(bool enable)
	{
		_enable_zwrite = enable;
	}

	void KiteDriverRenderStateSetter::StateSet()
	{
		glDepthMask(_enable_zwrite);
	}
}