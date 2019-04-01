#include"class_mutex.1.hpp"
int main()
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
		threads.push_back(std::thread(&Massive::summ, a, b, c));
	}
	return 0;
}