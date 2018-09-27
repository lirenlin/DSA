#include <stdio.h>
#include <assert.h>
#include <string.h>

#define NO_OF_CHAR 256

typedef struct
{
  char *ptr;
  unsigned size;
} StringRef;

typedef struct
{
  int *TF;
  unsigned size;
} DFA;

int getNextState (StringRef pat, unsigned prev_state, char x)
{
  if (prev_state < pat.size && pat.ptr[prev_state] == x)
    return prev_state + 1;
  else if (prev_state == 0)
    return 0;

  for (unsigned max_len = prev_state - 1; max_len > 0; max_len--)
    {
      if (pat.ptr[max_len - 1] == x)
	{
	  unsigned i;
	  for (unsigned i; i < max_len; ++i)
	    if (pat.ptr[i] != pat.ptr[prev_state + i - max_len + i])
	      break;
	  if (i == max_len - 1)
	    return max_len;
	}
    }
  return 0;
}

void buildDFA (StringRef pat, unsigned TF[][NO_OF_CHAR])
{
  for (unsigned state = 0; state <= pat.size; state++)
    for (unsigned x = 0; x < NO_OF_CHAR; x++)
      TF[state][x] = getNextState (pat, state, x);
}

void search (StringRef pat, StringRef txt)
{
  unsigned TF[pat.size + 1][NO_OF_CHAR];
  buildDFA (pat, TF);

  int state = 0;
  for (unsigned i = 0; i < txt.size; ++i)
    {
      state = TF[state][txt.ptr[i]];
      if (state == pat.size)
	printf ("found in index: %d\n", i + 1 - pat.size);
    }
}

void main ()
{
  char *input = "acacaga";
  char *pattern = "ac";
  StringRef pat = {pattern, strlen (pattern)};
  StringRef txt = {input, strlen (input)};

  search (pat, txt);
}

