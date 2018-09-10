#include <iostream>
#include <vector>
#include <algorithm>

using VL = std::vector<int>;
VL mergeAndSort(VL vl1, VL vl2)
{
  VL result;
  std::sort (vl1.begin (), vl1.end ());
  std::sort (vl2.begin (), vl2.end ());

  int i = 0, j = 0;
  int dup = -1;
  while (i < vl1.size() && j < vl2.size ())
    {
      int a = vl1[i];
      int b = vl2[j];

      if (a == dup)
	{
	  i++;
	  continue;
	}
      if (b == dup)
	{
	  j++;
	  continue;
	}

      if (a < b)
	{
	  result.push_back (a);
	  ++i;
	}
      else if (a == b)
	{
	  dup = a;
	  result.push_back (a);
	  ++i;
	  ++j;
	}
      else
	{
	  result.push_back (b);
	  ++j;
	}
    }

  if (i < vl1.size())
    result.insert (result.end (), vl1.begin () + i, vl1.end ());
  if (j < vl2.size())
    result.insert (result.end (), vl2.begin () + i, vl2.end ());

    return result;
}

int main ()
{
  VL vl1 = {1, 3, 2, 3, 5, 4};
  VL vl2 = {0, 3, 2, 4, 5, 6};

  VL res = mergeAndSort (vl1, vl2);
  for (auto I : res)
    std::cout << I << ' ';
  std::cout << '\n';

}
