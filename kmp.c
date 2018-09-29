#include <stdio.h>
#include <string.h>

typedef struct
{
  char *ptr;
  unsigned size;
} StringRef;

void buildLPS_improved (StringRef pat, unsigned *LPS)
{
  LPS[0] = 0;
  unsigned i = 1;
  unsigned len = 0;
  while (i < pat.size)
    {
      if (pat.ptr[i] == pat.ptr[len])
	{
	  ++len;
	  LPS[i] = len;
	  i++;
	}
      else
	{
	  if (len != 0)
	    // look into substructure
	    // ABCAABCAA--G, 0-len == -len: LPC[len -1] == LPC[i]
	    // 000112345
	    len = LPS[len - 1];
	  else
	    {
	      LPS[i] = 0;
	      i++;
	    }
	}
    }
}

void buildLPS (StringRef pat, unsigned *LPS)
{
  for (unsigned i = 0; i < pat.size; i++)
    {
      LPS[i] = 0;
      int len = i;
      for (len; len > 0; len--)
	{
	  unsigned m = 0;
	  for (m; m < len; m++)
	    if (pat.ptr[m] != pat.ptr[m + i + 1 -len])
	      break;
	  if (m == len)
	    {
	      LPS[i] = len;
	      break;
	    }
	}
    }
}

void find (StringRef pat, StringRef txt)
{
  unsigned LPS[pat.size];
  buildLPS_improved (pat, LPS);

  int i = 0, j = 0;

  while (j < txt.size)
    {
      if (pat.ptr[i] == txt.ptr[j])
	{
	  i++;
	  j++;
	}
      else
	{
	  i = LPS[i-1];
	  // if i == 0, we move j
	  if (i == 0)
	    j += 1;
	}

      if (i == pat.size)
	{
	  printf ("found in index: %d\n", j - pat.size);
	  // This is needed
	  i = LPS[i-1];
	}
    }
}

void main ()
{

  char *text = "li ren lin";
  char *pattern = "li";
  StringRef txt = {text, strlen (text)};
  StringRef pat = {pattern, strlen (pattern)};

  find (pat, txt);
}
