#include <iostream>
#include <string>

class Solution {
public:
    int monotoneIncreasingDigits (int N)
      {
	int idx = 1;
	std::string str = std::to_string (N);
	int mark = -1;
	while (idx < str.size ())
	  {
	    if (mark != -1)
	      {
		str[idx] = '9';
	      }
	    else if (str[idx - 1] > str[idx])
	      {
		str[idx] = '9';
		mark = idx - 1;
	      }

	    idx++;
	  }

	if (mark != -1)
	  {
	    str[mark] = str[mark] - 1;
	    while (mark != 0 && str[mark] < str[mark-1])
	      {
		str[mark-1] = str[mark];
		str[mark] = '9';
		mark--;
	      }
	  }
	return std::stoi (str);
      }
};

int main ()
{
  int i;
  std::cout << "give a number: ";
  std::cin >> i;
  Solution solution;
  std::cout << solution.monotoneIncreasingDigits (i) << std::endl;
  return 0;
}
