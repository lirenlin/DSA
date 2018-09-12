#include <iostream>
#include <algorithm>
#include <vector>

int printVec (std::vector<int> &vec)
{
  for (auto i: vec)
    std::cout << i << ' ';

  std::cout << std::endl;
}

int main ()
{
  std::vector<int> vec = {1, 5, 9, 4, 3, 2, 8};
  std::make_heap (vec.begin (), vec.end ());
  std::cout << "org heap:";
  printVec (vec);

  std::pop_heap (vec.begin (), vec.end ());
  std::cout << "pop heap:";
  printVec (vec);

  int max_elem = vec.back ();
  std::cout << "max element:";
  std::cout << max_elem << std::endl;
  vec.pop_back ();
  std::cout << "after pop heap:";
  printVec (vec);

  vec.push_back (10);
  std::cout << "push back new element:";
  printVec (vec);

  std::push_heap (vec.begin (), vec.end ());
  printVec (vec);

  return 0;
}
