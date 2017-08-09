int
isPrime (int num)
{
  /* Handle the common case.
     This will cover most of the case.  */
  if (num == 1 || num == 2 || num == 3)
    return 1;

  if (num % 3 == 0)
    return 0;
  if (num % 2 == 0)
    return 0;

  int i;
  for (i = 2; i*i < num; i++)
    if (num % i == 0)
      return 0;

  return 1;
}

int
main (int argc, const char *argv[])
{
  int n;
  unsigned result;
  printf("Enter a positive number: ");
  scanf ("%d", &n);
  result = isPrime (n);
  if (result)
    printf("%d is a prime number.\n", n);
  else
    printf("%d is not a prime number.\n", n);

  return 0;
}
