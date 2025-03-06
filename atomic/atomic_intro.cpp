#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void add(std::atomic<int> &num){
    for(int i = 0; i < 10000000; i++){
        ++num;
    }
}

int main(){
    std::atomic<int> num{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 4;i++){
        threads.emplace_back(add, std::ref(num));
    }
    for(auto &thread : threads){
        thread.join();
    }
    std::cout<<num<<std::endl;
    //40000
}

