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
	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
	switch (choosenumber)
	{
		case 1:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b)  b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{

				threads.push_back(std::thread(&MassiveTryMutex::SummFirstTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			stop = std::chrono::high_resolution_clock::now();
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"First done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}

		case 2:
		{	
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{	
				threads.push_back(std::thread(&MassiveTryMutex::SummSecondTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			stop = std::chrono::high_resolution_clock::now();
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"Second done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}
		case 3:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{
				threads.push_back(std::thread(&MassiveTryMutex::SummThirdTask, tryMutex, a, b, c));
				a = std::rand()%10;
				b = std::rand()%10;
				while (a==b) b = std::rand()%10;
				c = std::rand()%10;
				while (a==c || b==c) c = std::rand()%10;
			}
			stop = std::chrono::high_resolution_clock::now();
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"Third done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}
		case 4:
		{
			int a = std::rand()%10;
			int b = std::rand()%10;
			while (a==b) b = std::rand()%10;
			int c = std::rand()%10;
			while (a==c || b==c) c = std::rand()%10;

			start = std::chrono::high_resolution_clock::now();
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
			stop = std::chrono::high_resolution_clock::now();
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"Forth done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
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
