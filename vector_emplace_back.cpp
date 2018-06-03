//https://en.cppreference.com/w/cpp/container/vector/emplace_back
//Appends a new element to the end of the container.
//The element is constructed through std::allocator_traits::construct, which
//typically uses placement-new to construct the element in-place at the
//location provided by the container.

#include <iostream>
#include <string>
#include <vector>

class Flower
{
public:
  Flower (std::string name): name (name)
  {
    std::cout << "I am being constructed.\n";
  }

  Flower (Flower &&other): name (other.name)
  {
    std::cout << "I am being moved.\n";
  }

  Flower& operator=(const Flower &other) = default;
private:
  std::string name;
};

int main ()
{
  std::vector<Flower> flowers;
  // To avoid vector capacity change. This will cause move ctor been called.
  flowers.reserve (10);
  std::cout << "emplace_back:\n";
  flowers.emplace_back ("rose");

  std::cout << "push_back:\n";
  flowers.push_back (Flower ("lavender"));

  std::cout << "push_back:\n";
  flowers.push_back (Flower ("apple"));
}
