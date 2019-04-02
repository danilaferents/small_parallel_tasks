#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ctime>

std::mutex mutextask2;
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