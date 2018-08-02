#pragma once

namespace kite_driver
{

	template <class... ARGS> class KiteDriverEvent
	{
	public:
		typedef std::function<void(ARGS...)> EventArgsDelegate;
		typedef std::shared_ptr<EventArgsDelegate> EventArgsDelegatePtr;

		void RegistryEvent(EventArgsDelegatePtr func)
		{
			if (std::find_if(_events.begin(), _events.end(), [&func](auto f)
			{
				return f.lock() == func;
			}) == _events.end())
			{
				_events.push_back(func);
			}
		}

		void UnregistryEvent(EventArgsDelegatePtr func)
		{
			auto found_iter = std::find_if(_events.begin(), _events.end()
				, [&func](auto f)
			{
				return f.lock() == func;
			});
			if (found_iter != _events.end())
			{
				_events.erase(found_iter);
			}
		}

		void Invoke(ARGS... args)
		{
			std::for_each(_events.begin(), _events.end(), [&args...](auto func)
			{
				(*func.lock())(args...);
			});
		}

	private:
		std::vector<std::weak_ptr<EventArgsDelegate>> _events;
	};
}