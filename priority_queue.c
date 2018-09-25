#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
typedef struct
{
  int key;
  int data;
} Node;

typedef struct
{
  unsigned size;
  Node *root[MAX];
  unsigned max;

} NodeHeap;

unsigned cmp (NodeHeap *heap, int idx1, int idx2)
{
  return (heap->root[idx1]->key > heap->root[idx2]->key);
}

void initHeap (NodeHeap *heap)
{
  heap->size = 0;
  heap->max = MAX;
}

void swapNode (NodeHeap *heap, unsigned idx1, unsigned idx2)
{
  Node *tmp = heap->root[idx1];
  heap->root[idx1] = heap->root[idx2];
  heap->root[idx2] = tmp;
}

// Max node between parent and two children
void swapUp (NodeHeap *heap, unsigned child_idx)
{
  if (child_idx == 0)
    return;

  do
    {
      unsigned p_idx = (child_idx - 1) / 2;
      if (cmp (heap, child_idx, p_idx))
	{
	  swapNode (heap, child_idx, p_idx);
	  child_idx = p_idx;
	}
      else
	break;
    } while (child_idx != 0);
}

// Max node between parent and two children
void swapDown (NodeHeap *heap, unsigned parent_idx)
{
  unsigned p_idx = parent_idx;
  unsigned l_idx = p_idx * 2 + 1;
  unsigned r_idx = l_idx + 1;

  while (1)
    {
      // No child node
      if (l_idx >= heap->size)
	break;

      // single left child node
      if (l_idx == heap->size - 1)
	{
	  if (cmp (heap, l_idx, p_idx))
	    swapNode (heap, l_idx, p_idx);
	  break;
	}

      // two children
      unsigned cmp1 = cmp (heap, l_idx, r_idx);
      unsigned cmp2 = cmp (heap, l_idx, p_idx);
      unsigned cmp3 = cmp (heap, r_idx, p_idx);

      if (cmp1 && cmp2)
	{
	  swapNode (heap, l_idx, p_idx);
	  p_idx = l_idx;
	}
      else if (!cmp1 && cmp3)
	{
	  swapNode (heap, r_idx, p_idx);
	  p_idx = r_idx;
	}
      else
	break;

      l_idx = p_idx * 2 + 1;
      r_idx = l_idx + 1;
    }
}


void dumpHeap (NodeHeap *heap)
{
  static unsigned idx = 0;
  char fileName[20];
  sprintf (fileName, "priority_queue_%d.dot", idx);
  idx += 1;

  FILE *f = fopen (fileName, "w");
  if (f == NULL)
    {
      printf ("Error while open file!\n");
      exit (1);
    }
  else
    printf ("Writing %s!\n", fileName);

  fprintf (f, "digraph \"queue\" {\n");

  //dump al the node
  for (unsigned i = 0; i < heap->size; ++i)
    fprintf (f, "Node%p [label=\"priority: %d, val: %d\"];\n", heap->root[i], heap->root[i]->key,
	    heap->root[i]->data);

  //dump the link
  for (unsigned i = 0; i < heap->size; ++i)
    {
      unsigned l_idx = i * 2 + 1;
      unsigned r_idx = l_idx + 1;
      if (l_idx < heap->size)
	fprintf (f, "Node%p -> Node%p\n", heap->root[i], heap->root[l_idx]);
      else
	break;
      if (r_idx < heap->size)
	fprintf (f, "Node%p -> Node%p\n", heap->root[i], heap->root[r_idx]);
      else
	break;
    }

  fprintf (f, "}\n");
  fclose (f);
}

bool insert (NodeHeap *heap, Node *node)
{
  unsigned idx = heap->size;
  if (idx == MAX)
    return false;

  heap->root[idx] = node;
  heap->size += 1;

  swapUp (heap, idx);
  return true;
}

Node *removeMax (NodeHeap *heap)
{
  if (heap->size == 0)
    return NULL;

  unsigned last_idx = heap->size - 1;
  heap->size = last_idx;

  Node *res = heap->root[0];
  heap->root[0] = heap->root[last_idx];
  heap->root[last_idx] = NULL;

  swapDown (heap, 0);
}

void main ()
{
  NodeHeap heap;
  initHeap (&heap);

  Node node1 = {10, 10};
  Node node2 = {0, 0};
  Node node3 = {1, 1};
  Node node4 = {2, 2};
  Node node5 = {3, 3};
  Node node6 = {5, 5};
  Node node7 = {4, 4};

  insert (&heap, &node2);
  insert (&heap, &node3);
  insert (&heap, &node4);
  insert (&heap, &node5);
  insert (&heap, &node1);
  insert (&heap, &node6);
  dumpHeap (&heap);
  removeMax (&heap);
  dumpHeap (&heap);
  insert (&heap, &node7);
  dumpHeap (&heap);
  removeMax (&heap);
  dumpHeap (&heap);

}
