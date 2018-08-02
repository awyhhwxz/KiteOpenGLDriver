namespace kite_driver
{
	template<class T> class KiteDriverTempObjectGetter
	{
	public:
		std::shared_ptr<T> GetTemporaryObject()
		{
			std::shared_ptr<T> result_obj;
			if (_temp_obj_pool.empty())
			{
				result_obj = std::make_shared<T>();
			}
			else
			{
				result_obj = _temp_obj_pool.top();
				_temp_obj_pool.pop();
			}

			_shared_list.push_back(result_obj);
			return result_obj;
		}
		void ReleaseTemporaryObject(const std::shared_ptr<T>& temp_obj)
		{
			auto found_iter = std::find(_shared_list.begin(), _shared_list.end(), temp_obj);
			if (found_iter != _shared_list.end())
			{
				_shared_list.erase(found_iter);
				_temp_obj_pool.push(temp_obj);
			}
		}

	private:
		std::vector<std::shared_ptr<T>> _shared_list;
		std::stack<std::shared_ptr<T>> _temp_obj_pool;
	};
}