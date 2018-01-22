#include <stdio.h>
#include <assert.h>

char *strcpy (char *destination, const char *source)
{
  assert ((destination != NULL) && (source != NULL));
  char *result = destination;

  while ((*destination++ = *source++) != '\0')
    ;
  return result;
}

int strlen (const char *str)
{
  int len = 0;
  assert (str != NULL);
  while (*str++ != '\0')
    len++;
  return len;
}

char *strcat (char *destination, const char *source)
{
  assert ((destination != NULL) && (source != NULL));
  char *result = destination;

  while (*destination != '\0')
    ++destination;

  while ((*destination++ = *source++) != '\0')
    ;
  return result;
}

int strcmp (const char *str1, const char *str2)
{
  assert ((str1 != NULL) && (str2 != NULL));

  while (*str1 == *str2)
    {
      if (*str1 == '\0')
	return 0;
      ++str1;
      ++str2;
    }

  return *str1 - *str2;
}

void main ()
{
  char str1[50] = "Hello World!";
  char str2[] = "Hello World!";

  printf("%d\n", strcmp (str1, str2));
  strcat (str1, str2);
  printf("%s %d\n", str1, strlen (str1));
  strcpy (str1, str2);
  printf("%s\n", str1);
}
