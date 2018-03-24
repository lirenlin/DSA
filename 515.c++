#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode (int x): val (x), left (NULL), right (NULL) {}
  TreeNode (int x, TreeNode *left, TreeNode *right): val (x), left (left), right (right) {}
};

class Solution
{
public:
  vector<int> largestValues (TreeNode *root)
    {
      vector<int> result;
      if (root == nullptr)
	return result;

      vector<TreeNode *> queue;
      queue.push_back (root);
      int max = numeric_limits<int>::min ();
      int current_row = 1;
      int next_row = 0;
      int idx = 0;

      while (current_row)
	{
	  TreeNode *node = queue[idx++];
	  if (node->left != nullptr)
	    {
	      queue.push_back (node->left);
	      next_row++;
	    }
	  if (node->right != nullptr)
	    {
	      next_row++;
	      queue.push_back (node->right);
	    }
	  current_row--;

	  if (max < node->val)
	    max = node->val;

	  if (current_row == 0)
	    {
	      result.push_back (max);
	      current_row = next_row;
	      next_row = 0;
	      max = numeric_limits<int>::min ();
	    }
	}
      return result;
    }
};

static int x = []() { std::ios::sync_with_stdio(false); cin.tie(NULL); return 0; }();
int
main ()
{
  TreeNode node7 = {10};
  TreeNode node6 = {9};
  TreeNode node5 = {3};
  TreeNode node4 = {5};
  TreeNode node3 = {2, &node7, &node6};
  TreeNode node2 = {3, &node4, &node5};
  TreeNode node1 = {1, &node2, &node3};

  Solution solution;
  vector<int> result = solution.largestValues (&node1);
  for (auto val: result)
    cout << val << ' ';
  cout << endl;
}
