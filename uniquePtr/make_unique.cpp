#include <iostream>
#include <memory>

class Foo {
    int a,b;

public:
    Foo(int a, int b):a(a),b(b){std::cout<<"Constuctor called!"<<std::endl;}
    void print() {std::cout<<"a: "<<a<<", b: "<<b<<std::endl;}
    ~Foo() {std::cout<<"Destructor called!"<<std::endl;}
};

int main() {
    auto ptr=std::make_unique<Foo>(1,2);
    ptr->print();
}
