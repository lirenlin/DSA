#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define debug_print(fmt, ...) \
  do { if (DEBUG) printf (fmt, __VA_ARGS__); } while (0);
#else
#define debug_print(fmt, ...)
#endif

void reverseChar (char *start, char *end)
{
  if (start >= end)
    return;

  while (start < end)
    {
      char tmp = *end;
      *end = *start;
      *start = tmp;

      end--;
      start++;
    }
}

void reverseChar (char *start, unsigned size)
{
  if (size <= 1)
    return;

  reverseChar (start, start+size-1);
}

void reverseWord (char *str)
{
  char *wordS = str;
  char *wordE = str;
  char *currentC = str;
  char *strE;

  while (true)
    {
      if (*currentC == ' ' )
	{
	  wordE = currentC - 1;
	  reverseChar (wordS, wordE);
	  wordS = currentC + 1;
	}
      else if (*currentC == '\0')
	{
	  wordE = currentC - 1;
	  reverseChar (wordS, wordE);
	  break;
	}

      currentC++;
    }
  debug_print ("stage1: %s\n", str);
  strE = currentC - 1;

  reverseChar (str, strE);
  debug_print ("stage2: %s\n", str);
}

#define STR_SIZE 50
int main ()
{
  char string[STR_SIZE];
  memset (string, '\0', STR_SIZE);
  printf ("Enter a string: ");
  fgets (string, STR_SIZE, stdin);


  // Remove the trailing newline
  unsigned size = strlen (string);
  if (size > 0 && string[size - 1] == '\n')
      string[size - 1] = '\0';
  debug_print ("%s\n", string);

  reverseWord (string);
  printf ("reversed words are: %s\n", string);
}
