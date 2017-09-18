#include <iostream>
#include <array>

using namespace std;

// O(n) speed, O(n) space
void rotate (int *array, unsigned size, int k)
{
  unsigned index = 0;
  int *res = new int [10];

  for (index; index < size; index++)
    {
      int tmp = index + k;
      if (tmp >= size)
	tmp %= size;
      else if (tmp < 0)
	tmp = tmp + size;

      res[tmp] = array[index];
    }

  for (index = 0; index < size; index++)
      array[index] = res[index];

  delete[] res;
}

void swap (int *a, int *b)
{
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

// O(n) speed, O(1) space
void rotate_new (int *array, unsigned size, int k)
{
  unsigned processed = 0;
  unsigned index = 0;
  int val = array[0];

  while (processed < size)
    {
      int tmp;
      int new_index = index + k;

      if (new_index >= size)
	new_index %= size;
      else if (new_index < 0)
	new_index = new_index + size;

      tmp = array[new_index];
      array[new_index] = val;
      val = tmp;

      index = new_index;
      processed++;
    }
}


int main ()
{
  int array[] = {1, 2, 3, 4, 5, 6, 7};
  rotate (array, 7, 10);

  for (unsigned i = 0; i < 7; i++)
    cout << array[i] << " ";
  cout << endl;

  int array_new[] = {1, 2, 3, 4, 5, 6, 7};
  rotate_new (array_new, 7, 10);
  for (unsigned i = 0; i < 7; i++)
    cout << array_new[i] << " ";
  cout << endl;

  return 0;
}
