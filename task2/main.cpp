#include "class_mutex.hpp"
#include <algorithm>
void randomNumber(int&a, int&b, int&c)
{
	a = std::rand()%10;
	b = std::rand()%10;
	while (a==b)  b = std::rand()%10;
	c = std::rand()%10;
	while (a==c || b==c) c = std::rand()%10;
}
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
			int a=0,b=0,c=0;
			randomNumber(a,b,c);
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{
				randomNumber(a,b,c);
				threads.push_back(std::thread(&MassiveTryMutex::SummFirstTask, std::ref(tryMutex), a, b, c));
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			stop = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"First done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}

		case 2:
		{	
			int a=0,b=0,c=0;
			randomNumber(a,b,c);

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{	
				threads.push_back(std::thread(&MassiveTryMutex::SummSecondTask, std::ref(tryMutex), a, b, c));
				randomNumber(a,b,c);
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			stop = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"Second done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}
		case 3:
		{
			int a=0,b=0,c=0;
			randomNumber(a,b,c);

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{
				threads.push_back(std::thread(&MassiveTryMutex::SummThirdTask, std::ref(tryMutex), a, b, c));
				randomNumber(a,b,c);
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			stop = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = (stop-start); 
			std::cout<<std::endl<<"Third done! "<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
			break;
		}
		case 4:
		{
			int a=0,b=0,c=0;
			randomNumber(a,b,c);

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numb; ++i)
			{
				// std::cout<<a<<" "<<b<<" "<<c<<std::endl;
				threads.push_back(std::thread(&MassiveTryMutex::SummForthTask, std::ref(tryMutex), a, b, c));
				randomNumber(a,b,c);
			}
			std::for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
			stop = std::chrono::high_resolution_clock::now();
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
