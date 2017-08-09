typedef struct Node
{
  int data;
  Node *left;
  Node *right;
} Node;

int isIdentical (Node *root1, Node *root2)
{

}

/* Pre-order traversal.  root->left->right */
int isSubtree (Node *root1, Node *root2)
{

}

Node * newNode (int data)
{
  Node *node = (Node *)malloc (sizeof (Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

int main ()
{
  Node *tree1 = newNode (26);
  tree1->right = newNode (3);
  tree1->right->right = newNOde (3);
  tree1->left = newNode(10);
  tree1->left->left = newNode(4);
  tree1->left->left->right = newNode(30);
  tree1->left->right = newNode(6);

  Node *tree2 = newNode(10);
  tree2->right = newNode(6);
  tree2->left = newNode(4);
  tree2->left->right = newNode(30);

  if (isSubtree (tree1, tree2))
    printf("Tree2 is subtree of Tree 1\n");
  else
    printf("Tree2 is not subtree of Tree 1\n");

  return 0;
}
