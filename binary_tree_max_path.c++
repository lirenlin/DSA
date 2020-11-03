#include <iostream>
#include <limits.h>
#include <algorithm>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode (int val, TreeNode *left=nullptr, TreeNode *right=nullptr): val(val),
  left(left), right(right) {}
};


class Solution {
public:
  int helper(TreeNode *root) {
      if (root == nullptr)
	return 0;

      int max_left = helper(root->left);
      int max_right = helper(root->right);

      int max1 = root->val + std::max(max_left, max_right);
      int max2 = root->val + max_left + max_right;
      int max_up = std::max(max1, root->val);
      int max_current = std::max(max_up, max2);
      if (max_current > max_val)
	max_val = max_current;

      return max_up;
  }

  int maxPathSum (TreeNode *root) {
      int max_left = helper(root->left);
      int max_right = helper(root->right);
      int max = root->val + std::max(max_left, max_right);
      int max_close = root->val + max_left + max_right;

      max_val = std::max({max, max_close, max_val, root->val});
      return max_val;
  }
  int max_val = INT_MIN;
};

int main() {
    TreeNode n3(15);
    TreeNode n4(7);
    TreeNode n1(9);
    TreeNode n2(20, &n3, &n4);
    TreeNode n0(-10, &n1, &n2);

    Solution solution;
    std::cout << solution.maxPathSum(&n0) << std::endl;

    return 0;
}



