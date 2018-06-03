typedef struct Node
{
  struct Node *parent;
  struct Node *next;
  struct Node *child;
  char val;
} Node;

void pre_order (Node *pNode)
{
  bool process = true;
  while(pNode != NULL) {
      if(process) {
	  printf ("%c", pNode->val);
      }
      if(pNode->child != NULL && process) {
	  pNode = pNode->child;
	  process = true;
      } else if(pNode->next != NULL) {
	  pNode = pNode->next;
	  process = true;
      } else {
	  pNode = pNode->parent;
	  process = false;
      }
  }
}

void post_order (Node *pNode)
{
  bool nextLevel = true;

  while(pNode != NULL) {
      if (nextLevel == false)
	  printf ("%c", pNode->val);

      if(pNode->child == NULL)
	{
	  printf ("%c", pNode->val);
	  if (pNode->next != NULL)
	    {
	      pNode = pNode->next;
	      nextLevel = true;
	    }
	  else
	    {
	      pNode = pNode->parent;
	      nextLevel = false;
	    }
	}
      else if (nextLevel)
	pNode = pNode->child;
      else if (pNode->next != NULL)
	{
	  pNode = pNode->next;
	  nextLevel = true;
	}
      else
	pNode = pNode->parent;
  }
}

void main ()
{
}
