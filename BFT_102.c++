#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class Tree
{
public:
  Tree (T val, Tree<T> *left=NULL, Tree<T> *right=NULL):
    val (val), left (left), right (right) {};

  void bft ();

private:
  T val;
  Tree<T> *left;
  Tree<T> *right;
};

template <typename T>
void Tree<T>::bft ()
{
  queue< Tree<T> *> nodeQueue;

  nodeQueue.push (this);

  while (!nodeQueue.empty ())
    {
      Tree<T> *node = nodeQueue.front ();
      nodeQueue.pop ();
      if (node == NULL)
	continue;

      cout << node->val << ' ';
      if (node->left != NULL)
	nodeQueue.push (node->left);
      if (node->right != NULL)
	nodeQueue.push (node->right);
    }
  cout << endl;
}

int main ()
{
  Tree<int> node4 (3);
  Tree<int> node5 (4);
  Tree<int> node6 (4);
  Tree<int> node7 (3);
  Tree<int> node8 (5);

  Tree<int> node1 (2, &node6, &node8);
  Tree<int> node2 (2, &node4, &node5);
  Tree<int> node3 (2, &node6, &node7);

  Tree<int> root1 (1, &node2, &node3);
  Tree<int> root2 (1, &node2, &node1);

  root1.bft ();
  root2.bft ();
}
