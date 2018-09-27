#include <stdio.h>
#include <string.h>

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

int getNextState (StringRef pat)
{

}

void buildDFA (StringRef pat, DFA *table)
{

}

void search (StringRef pat, StringRef *txt)
{
  DFA table;
  buildDFA (pat, &table);
}

void main ()
{

}

