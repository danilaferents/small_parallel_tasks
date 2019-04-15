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
			races[a]=races[a] + races[b] + races[c];
			races[b]=races[a] + races[b] + races[c];
			races[c]=races[a] + races[b] + races[c];
		}
		void SummSecondTask(int a, int b, int c)
		{
			std::lock_guard<std::mutex> lock(mutextask2);
			races[a]=races[a] + races[b] + races[c];
			races[b]=races[a] + races[b] + races[c];
			races[c]=races[a] + races[b] + races[c];
		}
		void SummThirdTask(int a, int b, int c)
		{
			while(!std::try_lock(mutexvector[a], mutexvector[b], mutexvector[c]));
			races[a]=races[a] + races[b] + races[c];
			races[b]=races[a] + races[b] + races[c];
			races[c]=races[a] + races[b] + races[c];
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
			races[a]=races[a] + races[b] + races[c];
			races[b]=races[a] + races[b] + races[c];
			races[c]=races[a] + races[b] + races[c];
		}
};