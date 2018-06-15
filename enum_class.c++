#include <cstdint>
//https://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
//
// 1, strongly typed enums. old-style c++ enums are essentially integers;
// they could be compared with integers or with other enums of different type.
// 2, better scoping. old-style enum values were unscoped. You couldn't have two
// enumerations that shared the same name.
// 3, well-defined enum size. You can set the size of enum, signed or unsigned.

enum class Colors: std::int8_t { RED = 1, GREEN = 2, BLUE = 3};
enum class Feelings: char { EXCITED, MOODY, BLUE};
void func (Colors color);
