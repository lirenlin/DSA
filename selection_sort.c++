#include <iostream>
using namespace std;

template <typename T>
void dump_array (T array[], size_t size)
{
  for (int i = 0; i < size; ++i)
    cout << array[i] << " ";
  cout << endl;
}

template <typename T>
void swap (T *a, T *b)
{
  T tmp = *b;
  *b = *a;
  *a = tmp;
}

template <typename T>
void selection_sort (T array[], size_t size)
{
  int index = 0;

  while (index < size)
    {
      int max_index = index;
      T max = array[max_index];
      for (int i = index; i < size; i++)
	if (max < array[i])
	  {
	    max = array[i];
	    max_index = i;
	  }

      swap<T> (array+index, array+max_index);
      index++;
      dump_array (array, size);
    }
}

int main ()
{
  int array[] = {10, 2, 1, 3, 0, 7};
  selection_sort (array, 6);

  //dump_array (array, 6);
}
