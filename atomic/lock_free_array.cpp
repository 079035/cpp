#include <array>
#include <atomic>
#include <iostream>
#include <thread>

struct MyInt
{
    int n{0};
    std::atomic<bool> flag{flase};
};

class Stack
{
public:
    std::optional<int> getNum(int idx)
    {
        if(!mNums[idx].flag.load())
        {
            return std::nullopt;
        }
        return mNums[idx].n;
    }

    std::optional<int> pop_back()
    {
        int idx=mIdx.fetch_sub(1);
        if(idx<0)
        {
            mIdx.store(-1);
            return std::nullopt;
        }
        mNums[idx].flag.store(false);
        return mNums[idx].n;
    }

    void push_back(int num)
    {
        int idx = mIdx.fetch_add(1);
        ++idx;
        mNums[idx].n = num;
        mNums[idx].flag.store(true);
    }

private:
    std::atomic<int> mIdx{-1};
    std::array<MyInt,200> mNums;
};

int main()
{
    Stack st;
    std::thread t1([&st](){
        for(int i=0; i<100; ++i)
        {
            st.push_back(100);
        }
    });

    std::thread t2([&st](){
        for(int i=0; i<100; ++i)
        {
            st.push_back(100);
        }
    });
    t1.join();
    t2.join();
}
