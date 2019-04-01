#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ctime>

class MassiveFirstTask
{
	private:
		std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		// std::mutex some_mutex;
	public:
		// Massive(const vector<int>& races)
		// {
		// }
		MassiveFirstTask(){}
		MassiveFirstTask& operator=(MassiveFirstTask const&);
		void summ(int a, int b, int c)
		{
		//std::lock_guard<std::mutex> lock(some_mutex);
			std::cout<<races[a] + races[b] + races[c]<<" ";
		}
};