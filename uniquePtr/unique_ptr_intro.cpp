#include <iostream>
#include <memory>

class A{
    int *data;
public:
    A() {
        std::cout << "Resource Acquired!" << std::endl;
        data = new int[100];
    }

    void some() {std::cout<<"Can be used the same way as normal pointer"<<std::endl;}

    void do_sth(int a) {
        std::cout<<"Doing something!"<<std::endl;
        data[0]=a;
    }

    ~A() {
        std::cout<<"Resource Destroyed!"<<std::endl;
        delete[] data;
    }
};

void do_something(A* ptr) { 
    ptr->do_sth(3);
}

int main() {
    std::unique_ptr<A> pa(new A());
    do_something(pa.get());
}
