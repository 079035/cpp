#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr = nullptr;

public:
    // Constructor: takes raw pointer ownership
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor: deletes managed object
    ~UniquePtr() {
        delete ptr;
    }

    // Delete copy constructor and copy assignment to prevent copying
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor: transfer ownership from 'other'
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment operator: clean up current, then take ownership
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Dereference operators
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Access to the raw pointer
    T* get() const {
        return ptr;
    }

    // Release ownership, return the raw pointer, and set internal ptr to nullptr
    T* release() {
        T* old = ptr;
        ptr = nullptr;
        return old;
    }

    // Reset the managed object, deleting the old one
    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }
};

// Example usage
struct Foo {
    Foo() { std::cout << "Foo created\n"; }
    ~Foo() { std::cout << "Foo destroyed\n"; }
    void greet() { std::cout << "Hello from Foo!\n"; }
};

int main() {
    {
        UniquePtr<Foo> p1(new Foo());  // Owns a Foo
        p1->greet();                   // Use '->' operator
        {
            UniquePtr<Foo> p2 = std::move(p1); // Transfer ownership
            if (!p1.get()) {
                std::cout << "p1 is now null.\n";
            }
            p2->greet();
        } // p2 goes out of scope, Foo is destroyed here
    } // p1 also goes out of scope (but it's already null)

    return 0;
}
