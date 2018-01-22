#include <iostream>
#include <string.h>

void swap (char *val1, char *val2)
{
  char tmp = *val2;
  *val2 = *val1;
  *val1 = tmp;
}

void reverse (char *str)
{
  size_t size = strlen (str);
  unsigned i = 0;

  while (i < size / 2)
    {
      swap (str+i, str+size-i-1);
      i++;
    }
}

int main ()
{
  char string[] = "Hello World!";
  std::cout << string << std::endl;
  reverse (string);
  std::cout << string << std::endl;
}

