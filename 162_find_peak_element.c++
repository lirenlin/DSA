#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> intVec;

void findPeakElement (intVec vec)
{
  intVec result;

  size_t size = vec.size ();
  for (int i = 0; i < size;)
    {
      if (i == 0)
	{
	  if (vec[1] < vec[0])
	    {
	      result.push_back (0);
	      i += 2;
	    }
	  else
	    i++;
	}
      else if (i == size -1)
	{
	  if (vec[i-1] < vec[i])
	    result.push_back (i);
	  break;
	}
      else
	{
	  if (vec[i-1] < vec[i]
	      && vec[i] > vec[i+1])
	    {
	      result.push_back (i);
	      i += 2;
	    }
	  else
	    i++;
	}
    }

  for (auto it : result)
    cout << it << " ";
  cout << endl;
}


int main ()
{
  intVec vect = {1, 0, 2, 3, 4, 5, 1, 6};
  findPeakElement (vect);

  return 0;
}
