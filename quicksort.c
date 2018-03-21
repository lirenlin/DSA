#include <stdio.h>

void swap (int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partitionNew (int *array, int low, int high)
{
  int pivot = array[high];
  int j = high;
  int i = low;

  while (1)
    {
      while (array[j] > pivot)
	j--;
      while (array[i] < pivot)
	i++;

      if (i >= j)
	return i;

      swap (array + i, array + j);
    }
}

int partition (int *array, int low, int high)
{
  int pivot = array[high];
  int i = low - 1;
  int j;

  for (j = low; j <= high; ++j)
    {
      if (array[j] <= pivot)
	{
	  ++i;
	  swap (array + i, array + j);
	}
    }
  return i;
}

void quickSort (int *array, int low, int high)
{
  if (low >= high)
    return;

  //int pi = partition (array, low, high);
  int pi = partitionNew (array, low, high);

  quickSort (array, low, pi - 1);
  quickSort (array, pi + 1, high);
}

void printArray (int *array, int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf ("%d ", array[i]);
  printf ("\n");
}

int main ()
{
  int array[] = {10, 7, 8, 9, 1, 5};
  int n = sizeof (array) / sizeof (array[0]);

  quickSort (array, 0, n-1);
  printArray (array, n);
  return 0;
}
