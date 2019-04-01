//
//  start_mutex.cpp
//  
//
//  Created by Мой Господин on 10/03/2019.
//

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ctime>

std::vector<int> races = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::mutex some_mutex;
void summ(int a, int b, int c, int& d)
{
	//std::lock_guard<std::mutex> lock(some_mutex);
	d = races[a] + races[b] + races[c]; 
}
int main(int argc, char const *argv[])
{
	int numb;
	std::cin>>numb;
	std::vector<std::thread> threads;
	std::srand(unsigned(std::time(0)));
	int a = std::rand()/10;
	int b = std::rand()/10;
	int c = std::rand()/10;
	for (int i = 0; i < numb; ++i)
	{
		threads.push_back(std::thread(summ, a, b, c));
	}
	return 0;
}
