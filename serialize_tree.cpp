#include <iostream>
using namespace std;

class TreeNode
{
public:
  TreeNode (int a): data (a), left (nullptr), right (nullptr) {};
  TreeNode (): data (0), left (nullptr), right (nullptr) {};
  ~TreeNode ();

public:
  TreeNode *left;
  TreeNode *right;
  char data;
};

void deleteTree (TreeNode *node)
{
  // post-order to delete a tree
  if (node == nullptr)
    return;

  deleteTree (node->left);
  deleteTree (node->right);
  delete node;
}

TreeNode::~TreeNode ()
{
  deleteTree (left);
  deleteTree (right);
}


void serializeTree (TreeNode *node, string *str)
{
  if (node == nullptr)
    {
      str->push_back ('0');
      return;
    }

  str->push_back (node->data);
  serializeTree (node->left, str);
  serializeTree (node->right, str);
}

int deserializeTree (TreeNode *node, string str, int idx)
{
  if (idx == str.size ())
    return idx;

  node->data = str[idx++];

  if (str[idx] == '0')
    {
      node->left = nullptr;
      idx++;
    }
  else
    {
      TreeNode *newNodeL = new TreeNode ();
      idx = deserializeTree (newNodeL, str, idx);
      node->left = newNodeL;
    }

  if (str[idx] == '0')
    {
      node->right = nullptr;
      idx++;
    }
  else
    {
      TreeNode *newNodeR = new TreeNode ();
      idx = deserializeTree (newNodeR, str, idx);
      node->right = newNodeR;
    }

  return idx;
}

int main ()
{
  string str = "124005003600700";
  TreeNode *root = new TreeNode ();

  deserializeTree (root, str, 0);
  string newStr;
  serializeTree (root, &newStr);
  cout << str << endl;
  cout << newStr << endl;

  return 0;
}
