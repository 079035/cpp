#include <iostream>

template <typename T>
class SharedPtr {
private:
    T* ptr = nullptr;          // The managed object.
    int* ref_count = nullptr;  // Pointer to the reference count.

    // Helper function to decrement the count and delete if needed.
    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }

public:
    // Default constructor: create an empty SharedPtr.
    SharedPtr() = default;

    // Constructor: takes ownership of a raw pointer.
    explicit SharedPtr(T* p) : ptr(p) {
        if (p) {
            ref_count = new int(1);
        }
    }

    // Copy constructor: increases the reference count.
    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    // Move constructor: take ownership and leave other empty.
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // Copy assignment operator.
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            // Release current object.
            release();

            // Copy from other.
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    // Move assignment operator.
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            // Release current object.
            release();

            // Take over other's resources.
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // Destructor: release the managed object if this is the last owner.
    ~SharedPtr() {
        release();
    }

    // Dereference operator.
    T& operator*() const {
        return *ptr;
    }

    // Member access operator.
    T* operator->() const {
        return ptr;
    }

    // Returns the raw pointer.
    T* get() const {
        return ptr;
    }

    // Returns the current reference count.
    int use_count() const {
        return ref_count ? *ref_count : 0;
    }

    // Returns true if the pointer is not null.
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// Example usage
struct Foo {
    Foo() { std::cout << "Foo constructed\n"; }
    ~Foo() { std::cout << "Foo destroyed\n"; }
    void greet() { std::cout << "Hello from Foo!\n"; }
};

int main() {
    {
        SharedPtr<Foo> sp1(new Foo());
        std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 1

        {
            SharedPtr<Foo> sp2 = sp1; // Copy, ref count increases.
            std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 2
            std::cout << "sp2 use_count: " << sp2.use_count() << "\n"; // 2

            sp2->greet();
        } // sp2 goes out of scope, ref count decreases.

        std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 1

        SharedPtr<Foo> sp3 = std::move(sp1); // Move ownership.
        std::cout << "sp3 use_count: " << sp3.use_count() << "\n"; // 1
        std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 0 (empty)

        if (sp3) {
            (*sp3).greet();
        }
    } // sp3 goes out of scope, Foo is destroyed.

    return 0;
}
