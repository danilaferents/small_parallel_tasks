//
//  log.cpp
//  
//
//  Created by Danila Ferents on 28/04/2019.
//

#include "log.hpp"
#include <mutex>
#include <condition_variable>
#include <deque>
namespace MTDS {
	template <typename T>
	//thread safe  deque
	class Deque {
	public:
		Deque();
		~Deque()
		{
			std::lock_guard<std::mutex> _lock(deqmutex);
			_deque.clear();
		}

		template<typename... Args>
		void emplace_front(Args&&... args)
		{
			thrsafeAdd([&] {
				_deque.emplace_front(std::forward<Args>(args)...);
			});
		}

		template<typename... Args>
		void emplace_back(Args&&... args)
		{
			thrsafeAdd([&] {
				_deque.emplace_back(std::forward<Args>(args)...);
			});
		}
		//noexcept - для уведмоления компилятора о невозможности ошибок
		T pop_font() noexcept
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			while (_deque.empty()){
				waitData.wait(_lock);
			}
			auto firstelement = std::move(_deque.front());
			_deque.pop_front();
			return  firstelement;
		}
	private:
		template <class Class>
		void thrsafeAdd(Class&& _add)
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			_add();
			_lock.unlock();
			waitData.notify_one();
		}
		std::deque<T> _deque;
		mutable std::mutex deqmutex;
		std::condition_variable waitData;
	};

}
MTDS::Deque<int> ourdeque;
int main()
{

}