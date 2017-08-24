#include <stack>
#include <iostream>

using namespace std;

template <typename T>
class Tree
{
public:
  Tree (T val, Tree<T> *left=NULL, Tree<T> *right=NULL):
    val (val), left (left), right (right) {};

  bool isSymmetricTree ();
  void printTree ();

private:
  T val;
  Tree<T> *left;
  Tree<T> *right;
};

template <typename T>
bool Tree<T>::isSymmetricTree ()
{
  stack<Tree<T> *> stack1;
  stack<Tree<T> *> stack2;

  if (left == NULL && right == NULL)
    return true;
  if ((left == NULL && right != NULL)
      || (left != NULL && right == NULL))
    return false;

  stack1.push (left);
  stack2.push (right);

  while (!stack1.empty () && !stack1.empty ())
    {
      Tree<T> *node1 = stack1.top ();
      stack1.pop ();
      Tree<T> *node2 = stack2.top ();
      stack2.pop ();

      if (node1 == NULL && node2 == NULL)
	continue;
      else if ((node1 == NULL && node2 != NULL)
	       || (node1 != NULL && node2 == NULL))
	return false;

      if (node1->val == node2->val)
	{
	  stack1.push (node1->left);
	  stack1.push (node1->right);

	  stack2.push (node2->right);
	  stack2.push (node2->left);
	}
      else
	return false;
    }

  return (stack1.empty () && stack1.empty ());
}

template <typename T>
void Tree<T>::printTree ()
{

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

  cout << root1.isSymmetricTree () << endl;
  cout << root2.isSymmetricTree () << endl;
}
