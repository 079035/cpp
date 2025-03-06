#include <thread>
#include <iostream>
#include <chrono>
#include <string>

int fn()
{
    return 3;
}

int main()
{
    int num=0;
    std::thread t1([&num](){
        num = fn();
    });
    t1.join();

    std::cout << "retVal: " << num << std::endl;
}
