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
		else if (_type == KDPVT_FLOAT)
		{
			dataSize = sizeof(float);
		}
		else if (_type == KDPVT_VECTOR4)
		{
			dataSize = sizeof(kite_math::Vector4f);
		}
		else if (_type == KDPVT_VECTOR3)
		{
			dataSize = sizeof(kite_math::Vector3f);
		}

		if (_data.get() == nullptr)
		{
			switch (_type)
			{
			case KDPVT_MATRIX4F:
			case KDPVT_FLOAT:
			case KDPVT_VECTOR4:
			case KDPVT_VECTOR3:
				_data.reset(new uint8[dataSize]);
				break;
			}
		}

		memcpy(_data.get(), value, dataSize);
	}

	void * KiteDriverParaValue::GetValue()
	{
		return _data.get();
	}

}