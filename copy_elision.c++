#include <iostream>
#include <vector>
#include <utility>

struct Noisy {
    Noisy() { std::cout << this << " constructed\n"; }
    Noisy(const Noisy&) { std::cout << this << " copy-constructed\n"; }
    Noisy(Noisy&& ) { std::cout << this << " move-constructed\n"; }
    ~Noisy() { std::cout << this << " destructed\n"; }
    int val;
};

std::vector<Noisy> f() {
    std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision when initializing v
    // from a temporary (until C++17)
    // from a prvalue (since C++17)
    return v; // NRVO from v to the result object (not guaranteed, even in C++17)
}             // if optimization is disabled, the move constructor is called

Noisy g() {
    auto item = Noisy();
    item.val = 10;
    return item;
}

Noisy moveTest() {
    auto item = Noisy();
    item.val = 10;
    return std::move(item);
}

Noisy&& moveTest_Rval() {
    auto item = Noisy();
    item.val = 10;
    return std::move(item);
}

int main() {
    //Noisy n;			//default
    //Noisy m = n;		//copy
    //Noisy copy = std::move(n);	//move
    //Noisy x = g ();		//RVO, copy elision
    //const Noisy& lv_ref = g();

    // in order to return a Noisy object, another object is move created from
    // move expression, RVO applies to this object.
    //Noisy y = moveTest ();

    //std::move extend local object life time.
    //once left the context, the local object is destructed. However, there
    //is a reference returned which reference to illegal memory.
    Noisy z = moveTest_Rval ();

    return 0;
}
