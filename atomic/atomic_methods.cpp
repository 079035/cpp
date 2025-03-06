#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> n{0};
    int x=42;
    int y=3;

    bool result=n.compare_exchange_strong(x,y);
    // if (n==x){
    //  n=y;
    //  return true;
    // } else {
    //  x=n;
    //  return false;
    // }
}
