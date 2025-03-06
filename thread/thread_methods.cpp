#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

std::thread gThread;
void fn() {
    std::cout<<std::this_thread::get_id()<<std::endl;
}

void threadCaller() {
    gThread=std::thread(fn);
}

int main() {
    std::cout<<"# threads: "<<std::thread::hardware_concurrency()<<std::endl;
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    gThread.join();

    std::vector<std::thread> threads;
    for(int i=0;i<10;i++){
        threads.emplace_back(std::thread(fn));
    }
    for(auto &thread:threads){
        thread.join();
    }
}
