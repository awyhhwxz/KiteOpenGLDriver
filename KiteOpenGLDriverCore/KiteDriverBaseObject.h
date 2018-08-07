#pragma once

namespace kite_driver
{
	class KiteDriverBaseObject
	{
	public:
		KiteDriverBaseObject();
		~KiteDriverBaseObject();

		virtual KiteDriverObjectType get_type() = 0;

		inline const tstring& get_name() { return _name; }
		inline void set_name(const tstring& name) { _name = name; }
	protected:
		tstring _name;
	};
}

