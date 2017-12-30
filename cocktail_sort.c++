#include <iostream>
#include <algorithm>

using namespace std;

void cocktailSort (int array[], int size)
{
  int start = 0, end = size - 1;
  bool swapped = false;

  while (start != end)
    {
      swapped = false;
      for (int i = start; i < end; ++i)
	{
	  if (array[i] > array[i+1])
	    {
	      swap (array[i], array[i+1]);
	      swapped = true;
	    }
	}
      if (!swapped)
	break;

      --end;
      swapped = false;
      for (int i = end; i > start; --i)
	{
	  if (array[i] < array[i-1])
	    {
	      swap (array[i], array[i-1]);
	      swapped = true;
	    }
	}
      if (!swapped)
	break;

      ++start;
    }
}

void printArray (int array[], int size)
{
  for (int i = 0; i < size; ++i)
    cout << array[i] << " ";
  cout << endl;
}

int main ()
{
  int array [] = {5, 1, 4, 2, 8, 0, 2};
  int size = sizeof (array) / sizeof (int);

  cout << "before sort" << endl;
  printArray (array, size);
  cout << "after sort" << endl;
  cocktailSort (array, size);
  printArray (array, size);

  return 0;
}

