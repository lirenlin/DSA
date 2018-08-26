#include <iostream>
#include <vector>

struct Noisy {
    Noisy() { std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copy-constructed\n"; }
    Noisy(Noisy&&) { std::cout << "move-constructed\n"; }
    ~Noisy() { std::cout << "destructed\n"; }
};

std::vector<Noisy> f() {
    std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision when initializing v
    // from a temporary (until C++17)
    // from a prvalue (since C++17)
    return v; // NRVO from v to the result object (not guaranteed, even in C++17)
}             // if optimization is disabled, the move constructor is called

Noisy g() {
    return Noisy();
}

int main() {
    Noisy n;			//default
    Noisy m = n;		//copy
    Noisy copy = std::move(n);	//move
    Noisy x = g ();		//default
    return 0;
}
