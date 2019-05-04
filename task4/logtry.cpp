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

namespace MTDS {
	class Data {
	public:
		Data(const std::string msg, const std::thread::id _id, const int _flag) : threadMsg(msg), threadId(_id), flag(_flag) {}
		Data() : flag(0){}
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
			std::cout<<"Thread _id = "<<_data.returnId()<<std::endl<<"Message: "<<_data.returnMsg()<<std::endl;
			return _cout;
		}
		void changeToLast()
		{
			flag = 1;
		}
		int getFlag() const 
		{
			return flag;
		}
	private:
		std::string threadMsg;
		std::thread::id threadId;
		int flag;

	};
	//thread safe  deque
	class Deque {
	public:
		Deque()
		{

		};
		~Deque()
		{
			std::lock_guard<std::mutex> _lock(deqmutex);
			_deque.clear();
		}

		void emplace_font(Data&& _data)
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			_deque.emplace_front(_data);
			_lock.unlock();
			if (_data.getFlag()) waitData.notify_one();
		}

		void emplace_back(Data&& _data)
		{
			std::unique_lock<std::mutex> _lock(deqmutex);
			_deque.emplace_back(_data);
			if (_data)
			_lock.unlock();
			if (_data.getFlag()) waitData.notify_one();
		}
		//noexcept - для уведмоления компилятора о невозможности ошибок
		Data pop_font() noexcept
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
		// template <class Class>
		// void thrsafeAdd(Class&& _add)
		// {
		// 	std::unique_lock<std::mutex> _lock(deqmutex);
		// 	_add();
		// 	_lock.unlock();
		// 	waitData.notify_one();
		// }
		std::deque<Data> _deque;
		mutable std::mutex deqmutex;
		mutable std::condition_variable waitData;
	};
	class Logger {
	public:
		Logger() {}
		Logger(int _numThreads) : numThreads(_numThreads) {} 
		~Logger() {}
		void writeIntoFile() 
		{
			// std::ofstream _output;
			// _output.open("log.txt");

		 //    if (!_output) 
		 //    {
		 //        std::cerr << "File did not open!"<<std::endl;
		 //    }

			while(numThreads > 0)
			{
				auto _data = _deque.pop_font();
				std::cout<<_data;
			}
			numThreads-=1;
		}
		void emplace(const Data& _data) 
		{
			_deque.emplace_font(_data);
		}
		void incrNum()
		{
			numThreads+=1;
		}
	private:
		Deque _deque;
		// int deqLimit;
		int numThreads;
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
			Data _data(msg, threadId,0);
			std::this_thread::sleep_for(timeToSleep*numMult);
			_log.emplace(_data);
			// _log.incrNum();
		}
	private	:
		std::chrono::milliseconds timeToSleep;
	};
}
// std::mutex m;
int main()
{
	int numThr;
	std::cin>>numThr;
	MTDS::Logger _log(numThr);
	MTDS::Threads _threads(100);
	std::vector<std::thread> threads;
	for (int i = 0; i < numThr; ++i)
	{
		threads.push_back(std::thread(&MTDS::Threads::makeNote, std::ref(_threads), std::ref(_log), "Hello world!!!"));
	}
	auto loggerThr = std::thread(&MTDS::Logger::writeIntoFile, std::ref(_log));
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	loggerThr.join();
}