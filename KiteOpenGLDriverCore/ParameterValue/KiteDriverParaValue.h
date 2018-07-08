#pragma once


namespace kite_driver
{
	class KiteDriverParaValue
	{
	public:
		KiteDriverParaValue();
		~KiteDriverParaValue();

		void SetType(KiteDriverParaValueType type);
		KiteDriverParaValueType get_type() { return _type; }
		void SetValue(void* value);
		void* GetValue();

	private:
		std::unique_ptr<uint8> _data;
		KiteDriverParaValueType _type = KDPVT_INVALID;
	};

}