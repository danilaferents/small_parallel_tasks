#include "class_mutex.hpp"
#include <algorithm>
int main()
{
	int numb;
	std::cin>>numb;
	std::vector<std::thread> threads;
	int choosenumber = 0;
	std::cin>>choosenumber;
	MassiveTryMutex tryMutex; 
	switch (choosenumber)
	{
		case 1:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b)  b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			for (int i = 0; i < numb; ++i)
			{

				threads.push_back(std::thread(&MassiveTryMutex::SummFirstTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			break;
		}

		case 2:
		{	
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			for (int i = 0; i < numb; ++i)
			{	
				threads.push_back(std::thread(&MassiveTryMutex::SummSecondTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			break;
		}
		case 3:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			for (int i = 0; i < numb; ++i)
			{
				threads.push_back(std::thread(&MassiveTryMutex::SummThirdTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			break;
		}
		case 4:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			for (int i = 0; i < numb; ++i)
			{
				// std::cout<<a<<" "<<b<<" "<<c<<std::endl;
				threads.push_back(std::thread(&MassiveTryMutex::SummForthTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
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
