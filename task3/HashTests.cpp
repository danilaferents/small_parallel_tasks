#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <tuple>
#include <string>
#include<chrono>
#include<thread>
#include <functional>
#include "gtest/gtest.h"
#include "Hash.cpp"

// std::vector<std::string> hashFiles = {"/Users/danilafurenc/AllMyProjects/Shared/C++&CProjects/small_parallel_tasks/task3/hash_1.txt"};
std::vector<std::string> hashFiles = {"hash_1.txt"};
std::vector<std::string> hashExp = {"/Users/danilafurenc/AllMyProjects/Shared/C++&CProjects/small_parallel_tasks/task3/hash_exp.txt"};
int testnumber = 0;
int testnumberexp = 0;
std::tuple <std::vector<int>, std::vector<int>, int> read_info_from_file(std::string name_of_file)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    std::vector<std::thread> threads;
    MTDS::HashTable<int> hashMap;
    std::ifstream input(name_of_file);
    if (!input) 
    {
        std::cerr << "File did not open!"<<std::endl;
    }
    int howmanyoperations=0, findcount=0;
    start = std::chrono::high_resolution_clock::now();
    input >> howmanyoperations;
    
    std::vector<int> findbools;
    std::vector<int> findints;
    for (int i = 0; i < howmanyoperations; ++i)
    {
        int helpnumOper;
        input>>helpnumOper;
        switch(helpnumOper)
        {
            case 0:
            {
                int countOper;
                input>>countOper;
                for (int j = 0; j < countOper; ++j)
                {
                    int key, value;
                    input>>key>>value;
                    threads.push_back(std::thread(&MTDS::HashTable<int>::insert, std::ref(hashMap), key, value));
                }
                break;
            }
            case 1:
            {
                int countOper;
                input>>countOper;
                for (int j = 0; j < countOper; ++j)
                {
                    int key;
                    input>>key;
                    threads.push_back(std::thread(&MTDS::HashTable<int>::deleteValue, std::ref(hashMap), key));
                }
                break;
            }
            case 2:
            {
                int countOper;
                input>>countOper;
                findcount+=countOper;
                for (int j = 0; j < countOper; ++j)
                {
                    int key, value, result;
                    input>>key;                    
                    threads.push_back(std::thread(&MTDS::HashTable<int>::find, std::ref(hashMap), key, std::ref(value), std::ref(result)));
                    findbools.push_back(result);
                    findints.push_back(value);
                }
                break;
            }
            default:
            {
                std::cout<<"Invalid input";
            }
        }
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    testnumber++;
    
    stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = (stop-start); 
    std::cout<<std::endl<<"Done!"<<std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()<<"ms."<<std::endl;
    hashMap.Print();
    return std::make_tuple(findbools, findints, findcount);
}
// std::tuple<std::vector<int>, std::vector<int> > read_info_from_file_exp(std::string name_of_file)
// {
//     std::ifstream input(name_of_file);
//     if (!input) 
//     {
//         std::cerr << "File did not open!"<<std::endl;
//     }
//     std::vector<int> expectedbools, expectedints;
//     int exp;
//     int count=0;
//     input>>count;
//     for (int i = 0; i < count; ++i)
//     {
//         input>>exp;
//         expectedbools.push_back(exp);
//     }
//     for (int i = 0; i < count; ++i)
//     {
//        input>>exp;
//        expectedints.push_back(exp);
//     }
//     testnumberexp++;
//     return std::make_tuple(expectedbools, expectedints);
// }
TEST(TestsHash,TestInsertValue)
{
    // std::vector<int> expectedbools, expectedints, bools, ints;
    std::vector<int> expectedbools, expectedints, bools, ints;
    int count;
    // std::tie(expectedbools, expectedints) = read_info_from_file_exp(hashExp[testnumberexp]);
    std::tie(bools, ints,count) = read_info_from_file(hashFiles[testnumber]);
    ASSERT_EQ(count, bools.size());
    // std::cout<<expectedbools.size()<<expectedints.size()<<bools.size()<<ints.size();
    for (int i = 0; i < bools.size(); ++i)
    {
        std::cout<<bools[i]<<" ";
        // ASSERT_EQ(bools[i], expectedbools[i]);
        // ASSERT_EQ(ints[i], expectedints[i]);
    }
    for (int i = 0; i < ints.size(); ++i)
    {
        std::cout<<ints[i]<<" ";
    }


}
 //g++ --std=c++11 -stdlib=libc++ matrix_main.cpp matrix.cpp  -lgtest -lpthread -o MatrixTest
//valgrind   --leak-check=full --leak-resolution=high ./MatrixTest

