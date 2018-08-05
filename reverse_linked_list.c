#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
  Node *next;
  char data;
};

void printList (Node *root)
{
  Node *ptr = root;
  while (ptr != NULL)
    {
      printf ("%c", ptr->data);
      ptr = ptr->next;
    }
  printf ("\n");
}

Node *reverseList (Node *root)
{
  Node *prev, *current, *next;
  prev = root;
  current = root->next;
  root->next = NULL;

  while (current != NULL)
    {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
  return prev;
}

void main ()
{
  char string[] = "li renlin";
  Node *root = (Node *)malloc (sizeof (Node));
  root->data = string[0];
  root->next = NULL;

  Node *ptr = root;
  for (unsigned i = 1; i < strlen (string); ++i)
    {
      Node *node = (Node *) malloc (sizeof (Node));
      node->data = string[i];
      node->next = NULL;
      ptr->next = node;
      ptr = node;
    }

  printList (root);
  root = reverseList (root);
  printList (root);

  // free the dynamic allocation
  ptr = root;
  while (ptr != NULL)
    {
      Node *next = ptr->next;
      free (ptr);
      ptr = next;
    }
}
