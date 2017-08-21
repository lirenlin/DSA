#include <stdio.h>

void swap (int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void printArray (int *array, int size)
{
  int i;
  for (i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
}

int partition (int *array, unsigned size)
{
  int pivot = array[size - 1];
  int i = 0, index = -1;

  for (i = 0; i < size - 1; i++)
    {
      if (array[i] <= pivot)
	{
	  index++;
	  swap (&array[i], &array[index]);
	}
    }
  swap (&array[index+1], &array[size - 1]);

  return index+1;
}

void quickSort (int *array, unsigned size)
{
  if (size == 0 || size == 1)
    return;
  int loc = partition (array, size);
  quickSort (array, loc);
  quickSort (array + loc + 1, size - loc - 1);
}


int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}
