#include <iostream>
#include <thread>

int num = 0;

void plus10000()
{
    for (int i = 0; i < 10000; i++)
    {
        num++;
    }
}

int main() 
{
    std::thread t1(plus10000);
    std::thread t2(plus10000);
    
    t1.join();
    t2.join();

    std::cout << "num: " << num << std::endl;
}