//
//  log.cpp
//  
//
//  Created by Danila Ferents on 28/04/2019.
//

#include <mutex>
#include <condition_variable>
#include <deque>
//
#include <string>
#include <thread>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <chrono>
#include <vector>
#include <functional>

namespace MTDS2 {
	class Data {
	public:
		Data(const std::string msg, const std::thread::id _id) : threadMsg(msg), threadId(_id) {}
		~Data() {}
		std::string returnMsg() const
		{
			return threadMsg;
		}
		std::thread::id returnId() const
		{
			return threadId;
		}
		friend std::ostream& operator<<(std::ostream& _cout, const Data& _data)
		{
			_cout<<"Thread _id = "<<_data.returnId()<<std::endl<<"Message: "<<_data.returnMsg()<<std::endl;
			return _cout;
		}
	private:
		std::string threadMsg;
		std::thread::id threadId;
	};
	//thread safe  deque
	template <typename T>
	class Deque {
	public:
		Deque(): waitData(1){}
		~Deque()
		{
			std::lock_guard<std::mutex> _lock(deqmutex);
			_deque.clear();
		}

		template<typename... Args>
		void emplace_font(Args&&... args)
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
			while (waitData){
				_lock.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				_lock.lock();
			}
			auto firstelement = std::move(_deque.front());
			_deque.pop_front();
			if (_deque.empty()) waitData = 1;
			_lock.unlock();
			return  firstelement;
		}
	private:
		template <class Class>
		void thrsafeAdd(Class&& _add)
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			_add();
			waitData = 0;
			_lock.unlock();
		}
		std::deque<T> _deque;
		mutable std::mutex deqmutex;
		int waitData;
	};

	//thread safe  deque
	template <typename T>
	class DequeWithLim {
	public:
		DequeWithLim() : _deqlim(100), overSize(0), waitData(1) {}
		DequeWithLim(int deqlim) : _deqlim(deqlim) {} 
		~DequeWithLim()
		{
			std::lock_guard<std::mutex> _lock(deqmutex);
			_deque.clear();
		}

		template<typename... Args>
		void emplace_font(Args&&... args)
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
			while (waitData){
				_lock.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				_lock.lock();
			}
			auto firstelement = std::move(_deque.front());
			_deque.pop_front();
			if (_deque.empty()) waitData = 1;
			overSize = 0;
			_lock.unlock();
			return  firstelement;
		}
	private:
		template <class Class>
		void thrsafeAdd(Class&& _add)
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			while (overSize) {
				_lock.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				_lock.lock();
			}
			_add();
			if (_deque.size() == _deqlim) 
			{
				overSize = 1;
				// std::cout<<"Oversized";
			}
			waitData = 0;
			_lock.unlock();
		}
		std::deque<T> _deque;
		mutable std::mutex deqmutex;
		int _deqlim;
		int waitData;
		int overSize;
	};


	class Logger {
	public:
		Logger() {}
		Logger(int _numThreads) : numThr(_numThreads) {} 
		~Logger() {}
		void writeIntoFile(std::string _file) 
		{
			std::ofstream _output;
			_output.open(_file, std::ios::out | std::ios::trunc);

		    if (!_output) 
		    {
		        std::cerr << "File did not open!"<<std::endl;
		    }
			while(numThr>0)
			{
				auto _data = _deque.pop_font();
				_output<<"numThr: ";
				_output<<numThr;
				_output<<_data;
				numThr-=1;
			}
			
		}
		void writeIntoFileWithLim(std::string _file) 
		{
			std::ofstream _output;
			_output.open(_file, std::ios::out | std::ios::trunc);

		    if (!_output) 
		    {
		        std::cerr << "File did not open!"<<std::endl;
		    }
			while(numThr>0)
			{
				auto _data = _dequewithlim.pop_font();
				_output<<"numThr: ";
				_output<<numThr;
				_output<<_data;
				numThr-=1;
			}
			
		}
		void emplace(const Data& _data) 
		{
			_deque.emplace_font(_data);
		}
		void emplacewithlim(const Data& _data) 
		{
			_dequewithlim.emplace_font(_data);
		}
		void incrNum()
		{
			numThr+=1;
		}
	private:
		Deque<Data> _deque;
		DequeWithLim<Data> _dequewithlim;
		// int deqLimit;
		int numThr;
	};
	// int Logger::numThreads = 0;
	class Threads {
	public:
		Threads() : timeToSleep(100) {}
		~Threads() {}
		Threads(int sec) : timeToSleep(sec) {}
		void makeNote(Logger& _log, const std::string& msg) 
		{
			srand(static_cast<unsigned int>(time(0))); 
			int numMult = rand() %10;
			std::thread::id threadId = std::this_thread::get_id();
			Data _data(msg, threadId);
			std::this_thread::sleep_for(timeToSleep*numMult);
			_log.emplace(_data);
			// _log.incrNum();
		}
		void makeNoteWithLim(Logger& _log, const std::string& msg) 
		{
			srand(static_cast<unsigned int>(time(0))); 
			int numMult = rand() %10;
			std::thread::id threadId = std::this_thread::get_id();
			Data _data(msg, threadId);
			std::this_thread::sleep_for(timeToSleep*numMult);
			_log.emplacewithlim(_data);
			// _log.incrNum();
		}
	private	:
		std::chrono::milliseconds timeToSleep;
	};
}
// std::mutex m;
// int main()
// {
// 	int numThr;
// 	std::cin>>numThr;
// 	MTDS::Logger _log(numThr);
// 	MTDS::Threads _threads(1000);
// 	std::vector<std::thread> threads;
// 	for (int i = 0; i < numThr; ++i)
// 	{
// 		threads.push_back(std::thread(&MTDS::Threads::makeNote, std::ref(_threads), std::ref(_log), "Hello world!!!"));
// 	}
// 	auto loggerThr = std::thread(&MTDS::Logger::writeIntoFile, std::ref(_log));
// 	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
// 	loggerThr.join();
// }