#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode TreeNode;
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
};

bool isSameTree (TreeNode *root1, TreeNode *root2)
{
  if (root1 == 0 && root2 == 0)
    return true;
  if ((root1 == 0 && root2 != 0) || (root1 != 0 && root2 == 0))
    return false;
  if (root1->val != root2->val)
    return false;

  bool left_same = isSameTree (root1->left, root2->left);
  bool right_same = isSameTree (root1->right, root2->right);
  if (left_same && right_same)
    return true;
  else
    return false;
}

void main ()
{
  TreeNode leaf1 = {1, 0, 0};
  TreeNode leaf2 = {3, 0, 0};
  TreeNode leaf3 = {2, 0, 0};
  TreeNode root1 = {2, &leaf1, &leaf2};
  TreeNode root2 = {2, &leaf1, &leaf2};
  TreeNode root3 = {2, &leaf1, &leaf3};

  if (isSameTree (&root1, &root2))
    printf("Same tree\n");

  if (isSameTree (&root1, &root3))
    printf("Not the same tree\n");
}
