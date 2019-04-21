#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
std::vector<std::string> hashFiles = {"/Users/danilafurenc/AllMyProjects/Shared/C++&CProjects/small_parallel_tasks/task3/hash_2.txt", "hash_3.txt", "hash_4.txt"};
int main()
{
	int k;
	std::cin>>k;
	std::ofstream _output;
	_output.open(hashFiles[k], std::ios::out | std::ios::trunc);
    if (!_output) 
    {
        std::cerr << "File did not open!"<<std::endl;
        return 0;
    }
    int numberofoper = 0;
    std::cin>>numberofoper;
    _output<<numberofoper<<" "<<std::endl;

    for (int i = 0; i < numberofoper; ++i)
    {
    	int choose;
    	std::cin>>choose;
    	_output<<choose<<" ";
    	int count;
    	std::cin>>count;
    	if (count == 0) _output<<count/2<<" "<<std::endl;
    	else _output<<count<<" "<<std::endl;
    	for (int j = 0; j < count; ++j)
    	{
    		int _rand = std::rand() % 10000;
    		_output<<_rand<<" ";
    	}
    	_output<<std::endl;
    }
    _output.close();
}