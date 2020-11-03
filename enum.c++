#include <iostream>

enum class Color {RED, GREEN, BLUE};

template <typename E, E v>
std::string getNameImpl ()
{
  std::string fullName (__PRETTY_FUNCTION__);
  return fullName;
}

int main()
{
  //for gcc>=9, clang/llvm 5, the output string shall contain BLUE
  std::cout << getNameImpl<Color, Color::BLUE>() << std::endl;
  return 0;
}

