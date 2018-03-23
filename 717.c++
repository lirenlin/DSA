#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  bool isOneBitCharacter (vector<int>& bits)
    {
      int idx = 0;
      while (idx < bits.size ())
	{
	  if (bits[idx] == 0)
	    {
	      if (idx == bits.size () - 1)
		return true;
	      idx++;
	    }
	  else if (bits[idx] == 1)
	    idx += 2;
	}
      return false;
    }
};

int
main ()
{
  Solution solu;
  vector<int> input = {1, 0, 1, 0, 0};
  vector<int> input2 = {1, 1, 1, 0};
  bool result = solu.isOneBitCharacter (input);
  cout << result << endl;
  result = solu.isOneBitCharacter (input2);
  cout << result << endl;
}
