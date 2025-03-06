#include <iostream>
#include <queue>
using namespace std;

class RateLimiter {
public:
    RateLimiter(size_t N, uint64_t T): num_events_(N), time_window_(T) {}

    bool check(uint64_t now) {
        timestamps_.pop();
        timestamps_.push(now);

        if (time_window_ > now - timestamps_.front()) {
            return false;
        }
        return true;
    }

private:
    uint64_t time_window_;
    size_t num_events_;
    queue<uint64_t> timestamps_;
};

int main() {

}
