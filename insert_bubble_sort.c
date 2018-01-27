void swap (int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_array (int *array, int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf ("\n");
}

// O ( sum (n/2)) = O (n^2/4)
void insertion_sort (int *array, int size)
{
  int i, j;
  for (i = 0; i < size; ++i)
    {
      int val = array[i];
      if (i >0 && val >= array[i-1])
	continue;

      for (j = i; j >= 1; j--)
	{
	  if (val < array[j-1])
	    array[j] = array[j-1];
	  else
	    break;
	}
      array[j] = val;
    }
}

// O ( n + n -1 + n - 2 + ...) = O (n^2/2)
void bubble_sort (int *array, int size)
{
  int i, j;

  for (i = 0; i < size; ++i)
    {
      for (j = 0; j < size - i - 1; ++j)
	{
	  if (array[j] > array[j+1])
	    swap (array + j, array + j + 1);
	}
    }
}

void main ()
{
  int array [10] = {1, 2, 4, 3, 7, 9, 5, 6, 8, 0};
  //insertion_sort (array, 10);
  bubble_sort (array, 10);

  print_array (array, 10);

}
