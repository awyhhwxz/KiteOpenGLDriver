#include "stdafx.h"
#include "KiteDriverParaValue.h"


namespace kite_driver
{
	KiteDriverParaValue::KiteDriverParaValue()
	{
	}


	KiteDriverParaValue::~KiteDriverParaValue()
	{
	}
	void KiteDriverParaValue::SetType(KiteDriverParaValueType type)
	{
		_type = type;
	}

	void KiteDriverParaValue::SetValue(void* value)
	{
		int dataSize = 0;

		if (_type == KDPVT_MATRIX4F)
		{
			dataSize = sizeof(kite_math::Matrix4f);
		}

		if (_data.get() == nullptr)
		{
			if (_type == KDPVT_MATRIX4F)
			{
				_data.reset(new uint8[dataSize]);
			}
		}

		memcpy(_data.get(), value, dataSize);
	}

	void * KiteDriverParaValue::GetValue()
	{
		return _data.get();
	}

}