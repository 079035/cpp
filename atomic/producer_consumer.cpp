#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void producer(std::atomic<bool>& is_ready, int& data){
    data=10;
    is_ready.store(true, std::memory_order_release);
}

void consumer(std::atomic<bool>& is_ready, int& data){
    while(!is_ready.load(std::memory_order_acquire));
    std::cout<<"data: "<<data<<std::endl;
}

int main() {
    std::vector<std::thread> threads;
    std::atomic<bool> is_ready(false);
    int data=0;

    threads.push_back(std::thread(producer, std::ref(is_ready), std::ref(data)));
    threads.push_back(std::thread(consumer, std::ref(is_ready), std::ref(data)));

    for(int i=0;i<2;i++){
        threads[i].join();
    }
}
