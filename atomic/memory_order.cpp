#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
using std::memory_order_relaxed;

void t1(std::atomic<int>& a, std::atomic<int>& b) {
    b.store(1, memory_order_relaxed);
    int x = a.load(memory_order_relaxed);

    printf("x: %d\n", x);
}

void t2(std::atomic<int>& a, std::atomic<int>& b) {
    a.store(1, memory_order_relaxed);
    int y = b.load(memory_order_relaxed);

    printf("y: %d\n", y);
}


int main() {
    std::vector<std::thread> threads;

    std::atomic<int> a{0};
    std::atomic<int> b{0};

    threads.push_back(std::thread(t1, std::ref(a), std::ref(b)));
    threads.push_back(std::thread(t2, std::ref(a), std::ref(b)));

    for(int i=0;i<2;i++){
        threads[i].join();
    }
}