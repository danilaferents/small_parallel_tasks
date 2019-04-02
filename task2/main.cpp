#include "class_mutex.hpp"
#include <algorithm>
int main()
{
	int numb;
	std::cin>>numb;
	std::vector<std::thread> threads;
	int choosenumber = 0;
	std::cin>>choosenumber;
	std::srand(unsigned(std::time(0)));
	switch (choosenumber)
	{
		case 1:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			int c = std::rand()%10;
			MassiveFirstTask firstTask;
			for (int i = 0; i < numb; ++i)
			{
				
				threads.push_back(std::thread(&MassiveFirstTask::summ, firstTask, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				c = std::rand()%10;
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			break;
		}

		case 2:
		{	
			int a = std::rand()%10;
			int b = std::rand()%10;
			int c = std::rand()%10;
			MassiveSecondTask secondTask;
			for (int i = 0; i < numb; ++i)
			{
				
				threads.push_back(std::thread(&MassiveSecondTask::summ, secondTask, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				c = std::rand()%10;
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			break;
		}
		
		default:
		{
			std::cout<<"Choose another number!!!";
			break;
		}
	}
	return 0;
}
