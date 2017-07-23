#include <iostream>
// Rule of thumb
// A base class destructor should be either public and virtual,
// or protected and nonvirtual.

// For the first case, it allows polymorphic deletion. Delete a subclass with a
// pointer to a super-class. (or parent class/child class)

// Or totally dis-allow it by define the destructor as protected and
// nonvirtual, so the compiler will give an error when such code is written.

// http://www.gotw.ca/publications/mill18.htm

class Base {
    virtual void method() {std::cout << "method from Base" << std::endl;}
public:
    virtual ~Base() {
	std::cout << "Base destructor" << std::endl;
	method();
    }
    void baseMethod() {method();}
};

class A : public Base {
    void method() {std::cout << "method from A" << std::endl;}
public:
    ~A() {
	std::cout << "A destructor" << std::endl;
	method();
    }
};

int main(void) {
    Base* base = new A;
    base->baseMethod(); // A method
    delete base; // call A destructor, call B destructor
    return 0;
}
