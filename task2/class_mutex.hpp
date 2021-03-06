#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>

std::mutex mutextask2;
std::vector<std::mutex> mutexvector(10);
std::chrono::milliseconds interval(1);

class MassiveTryMutex
{
	private:
		std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	public:
		MassiveTryMutex(){}
		// MassiveFirstTask& operator=(MassiveFirstTask const&) = delete;
		void SummFirstTask(int a, int b, int c)
		{
			int summ = races[a] + races[b] + races[c];
			races[a]=summ;
			races[b]=summ;
			races[c]=summ;
		}
		void SummSecondTask(int a, int b, int c)
		{
			std::lock_guard<std::mutex> lock(mutextask2);
			int summ = races[a] + races[b] + races[c];
			races[a]=summ;
			races[b]=summ;
			races[c]=summ;
		}
		void SummThirdTask(int a, int b, int c)
		{
			while(!std::try_lock(mutexvector[a], mutexvector[b], mutexvector[c]));
			int summ = races[a] + races[b] + races[c];
			races[a]=summ;
			races[b]=summ;
			races[c]=summ;
			mutexvector[a].unlock();
			mutexvector[b].unlock();
			mutexvector[c].unlock();
		}
		void SummForthTask(int a, int b, int c)
		{
			if (a > b) std::swap (a,b);
			if (b > c) std::swap (b,c);
			if (a > b) std::swap (a,b);
			// std::scoped_lock _lock (mutexvector[a], mutexvector[b], mutexvector[c]);
			std::scoped_lock lock_a(mutexvector[a]);
			std::scoped_lock lock_b(mutexvector[b]);
			std::scoped_lock lock_c(mutexvector[c]);
			int summ = races[a] + races[b] + races[c];
			races[a]=summ;
			races[b]=summ;
			races[c]=summ;
		}
};
// while(true)
// {
// 	if(mutexvector[a].try_lock())
// 	{
// 		if (mutexvector[b].try_lock())
// 		{
// 			if (mutexvector[c].try_lock()) 
// 			{
// 				races[a]=races[a] + races[b] + races[c];
// 				races[b]=races[a] + races[b] + races[c];
// 				races[c]=races[a] + races[b] + races[c];
// 				mutexvector[a].unlock();
// 				mutexvector[b].unlock();
// 				mutexvector[c].unlock();
// 				break;
// 			}
// 			else
// 			{
// 				mutexvector[a].unlock();
// 				mutexvector[b].unlock();
// 				// std::this_thread::sleep_for(interval);
// 			}
// 		}
// 		else
// 		{
// 			mutexvector[a].unlock();
// 			// std::this_thread::sleep_for(interval);
// 		}
// 	} 
// }