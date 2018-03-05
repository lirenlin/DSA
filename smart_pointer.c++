#include <memory>
#include <iostream>

template <typename T>
using uniquePtr = std::unique_ptr<T>;

template <typename T>
using sharedPtr = std::shared_ptr<T>;

template  <typename T>
auto f(uniquePtr<T> &ptr) {
    *ptr = 42;
    return std::move (ptr);
}

template  <typename T>
auto f(sharedPtr<T> ptr) {
    *ptr = 12;
    return ptr;
}

int main() {
    auto ptr = std::make_unique<int>();
    ptr = f(ptr);

    auto p1 = std::make_shared<int>();
    p1 = f(p1);

    std::cout << *ptr + *p1 << std::endl;
}
