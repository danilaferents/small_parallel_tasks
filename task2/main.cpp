#include "class_mutex.hpp"
int main()
{
	int numb;
	std::cin>>numb;
	std::vector<std::thread> threads;
	std::srand(unsigned(std::time(0)));
	int a = std::rand()%10;
	int b = std::rand()%10;
	int c = std::rand()%10;
	for (int i = 0; i < numb; ++i)
	{
		MassiveFirstTask firstTask;
		a = std::rand()%10;
		b = std::rand()%10;
		c = std::rand()%10;
		threads.push_back(std::thread(&MassiveFirstTask::summ, firstTask, a, b, c));
	}
	std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
	return 0;
}