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
#include "log.cpp"
#include "log2.cpp"
std::vector<std::string> logFiles = {"log_1.txt", "log_2.txt", "log_3.txt", "log_4.txt"};
int testNum = 0;
TEST(TestsLog,Test1)
{
    int numThr=1000;
    MTDS::Logger _log(numThr);
    MTDS::Threads _threads(100);
    std::vector<std::thread> threads;
    for (int i = 0; i < numThr; ++i)
    {
        threads.push_back(std::thread(&MTDS::Threads::makeNote, std::ref(_threads), std::ref(_log), "Programming!!!"));
    }
    auto loggerThr = std::thread(&MTDS::Logger::writeIntoFile, std::ref(_log), logFiles[testNum]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    loggerThr.join();
    std::ofstream _file;
    _file.open(logFiles[testNum], std::ios_base::in | std::ios_base::app);
    _file<<"Test Number: "<<testNum + 1<<std::endl;
    _file.close();
    testNum++;
}
TEST(TestsLog,Test2)
{
    int numThr=500;
    MTDS::Logger _log(numThr);
    MTDS::Threads _threads(100);
    std::vector<std::thread> threads;
    for (int i = 0; i < numThr; ++i)
    {
        threads.push_back(std::thread(&MTDS::Threads::makeNoteWithLim, std::ref(_threads), std::ref(_log), "Writing!!!"));
    }
    auto loggerThr = std::thread(&MTDS::Logger::writeIntoFileWithLim, std::ref(_log), logFiles[testNum]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    loggerThr.join();
    std::ofstream _file;
    _file.open(logFiles[testNum], std::ios_base::in | std::ios_base::app);
    _file<<"Test Number: "<<testNum + 1<<std::endl;
    _file.close();
    testNum++;
}
TEST(TestsLog,Test3)
{
     int numThr=1000;
    MTDS2::Logger _log(numThr);
    MTDS2::Threads _threads(100);
    std::vector<std::thread> threads;
    for (int i = 0; i < numThr; ++i)
    {
        threads.push_back(std::thread(&MTDS2::Threads::makeNote, std::ref(_threads), std::ref(_log), "Working!!!"));
    }
    auto loggerThr = std::thread(&MTDS2::Logger::writeIntoFile, std::ref(_log), logFiles[testNum]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    loggerThr.join();
    std::ofstream _file;
    _file.open(logFiles[testNum], std::ios_base::in | std::ios_base::app);
    _file<<"Test Number: "<<testNum + 1<<std::endl;
    _file.close();
    testNum++;
}
TEST(TestsLog,Test4)
{
    int numThr=500;
    MTDS2::Logger _log(numThr);
    MTDS2::Threads _threads(100);
    std::vector<std::thread> threads;
    for (int i = 0; i < numThr; ++i)
    {
        threads.push_back(std::thread(&MTDS2::Threads::makeNoteWithLim, std::ref(_threads), std::ref(_log), "Hello world!!!"));
    }
    auto loggerThr = std::thread(&MTDS2::Logger::writeIntoFileWithLim, std::ref(_log), logFiles[testNum]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    loggerThr.join();
    std::ofstream _file;
    _file.open(logFiles[testNum], std::ios_base::in | std::ios_base::app);
    _file<<"Test Number: "<<testNum + 1<<std::endl;
    _file.close();
    testNum++;
}
 //g++-7 --std=c++11 -stdlib=libc++ log_main.cpp log.cpp  -lgtest -lpthread -o LogTests
//valgrind   --leak-check=full --leak-resolution=high ./LogTests
