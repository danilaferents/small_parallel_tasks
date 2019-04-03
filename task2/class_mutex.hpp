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

class MassiveFirstTask
{
	private:
		std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	public:
		MassiveFirstTask(){}
		// MassiveFirstTask& operator=(MassiveFirstTask const&) = delete;
		void summ(int a, int b, int c)
		{
			std::cout<<races[a] + races[b] + races[c]<<" ";
		}
};
class MassiveSecondTask
{
	private:
		 std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	public:
		MassiveSecondTask(){}
		void summ(int a, int b, int c)
		{
			std::lock_guard<std::mutex> lock(mutextask2);
			std::cout<<races[a] + races[b] + races[c]<<" ";
		}
};
class MassiveThirdTask
{
	private:
		 std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	public:
		MassiveThirdTask(){}
		void summ(int a, int b, int c)
		{
			// while(true)
			// {
			// 	if(mutexvector[a].try_lock())
			// 	{
			// 		std::cout<<"1 ";
			// 		if (mutexvector[b].try_lock())
			// 		{
			// 			std::cout<<"2 ";
			// 			if (mutexvector[c].try_lock()) 
			// 			{
			// 				std::cout<<"3 ";
			// 				// std::cout<<races[a] + races[b] + races[c]<<" ";
			// 				mutexvector[a].unlock();
			// 				mutexvector[b].unlock();
			// 				mutexvector[c].unlock();
			// 				break;
			// 			}
			// 			else
			// 			{
			// 				std::cout<<"4 ";
			// 				mutexvector[a].unlock();
			// 				mutexvector[b].unlock();
			// 				// std::this_thread::sleep_for(interval);
			// 			}
			// 		}
			// 		else
			// 		{
			// 			std::cout<<"5 ";
			// 			mutexvector[a].unlock();
			// 			// std::this_thread::sleep_for(interval);
			// 		}
			// 	} 
			// }
			while(!std::try_lock(mutexvector[a], mutexvector[b], mutexvector[c]));
			std::cout<<races[a] + races[b] + races[c]<<" ";
			mutexvector[a].unlock();
			mutexvector[b].unlock();
			mutexvector[c].unlock();
		}
};
class MassiveForthTask
{
	private:
		 std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	public:
		MassiveForthTask(){}
		void summ(int a, int b, int c)
		{
			if (a > b) std::swap (a,b);
			if (b > c) std::swap (b,c);
			if (a > b) std::swap (a,b);
			std::scoped_lock _lock{mutexvector[a], mutexvector[b], mutexvector[c]};
			std::cout<<races[a] + races[b] + races[c]<<" ";
		}
};