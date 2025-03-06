#include <thread>
#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <condition_variable>

class ThreadPool {
private:
    size_t num_threads_;
    std::vector<std::thread> worker_threads_;
    std::queue<std::function<void()>> jobs_;
    
    std::condition_variable cv_job_q_;
    std::mutex m_job_q_;
    
    // flag for termination
    bool stop_all;

public:
    
}

int main() {

}
