#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void worker(std::atomic<int>& counter) {
    for (int i = 0; i < 10000; i++) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::atomic<int> counter{0};
    std::vector<std::thread> workers;

    for(int i=0;i<4;i++){
        workers.emplace_back(std::thread(worker, std::ref(counter)));
    }

    for(int i=0;i<4;i++){
        workers[i].join();
    }

    std::cout << "counter: " << counter << std::endl;
}