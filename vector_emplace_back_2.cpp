#include <iostream>
#include <vector>

class Object
{
public:
    Object(std::string msg="null"): msg(msg)
    {
        std::cout << "default ctor:" << msg << "\n";
    }
    Object(Object&& other): msg(std::move(other.msg))
    {
        std::cout << "move ctor:" << msg << "\n";
    }
    Object(const Object& other): msg(other.msg)
    {
        std::cout << "copy ctor: " << other.msg << "\n";
    }
    Object& operator=(const Object& other)
    {
        msg = other.msg;
        std::cout << "copy assignment: " << msg << "\n";
        return *this;
    }
    Object& operator=(Object&& other)
    {
        msg = std::move(other.msg);
        std::cout << "move assignment: " << msg << "\n";
        return *this;
    }
private:
    std::string msg;
};

int main()
{
    // Don't use this
    //std::vector<Object> vector(10);
    std::vector<Object> vector;
    vector.reserve(10);
    Object tmp1("hello"); // default
    vector.emplace_back("this"); // default
    vector.emplace_back(std::move(tmp1)); // move
    vector.push_back(Object("why")); // default + move
    Object tmp2("tmp2");
    vector.push_back(tmp2); // copy ctor
    vector.push_back(std::move(tmp2)); // default + move
    vector.emplace_back(Object("again")); // default + move
    return 0;
}
