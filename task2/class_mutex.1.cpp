#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ctime>

class Massive
{
	private:
		std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		// std::mutex some_mutex;
	public:
		// Massive(const vector<int>& races)
		// {
		// }
		Massive(){}
		void summ(int a, int b, int c, int& d)
		{
		//std::lock_guard<std::mutex> lock(some_mutex);
			d = races[a] + races[b] + races[c]; 
		}
};