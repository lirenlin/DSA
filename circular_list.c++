#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
  explicit Node (T data): data (data), next (nullptr) {};

  void setNext (const Node node) {next = &node;};
  Node const* getNext () const {return next;};
  bool endP () const {next == nullptr;};

  friend ostream &operator << (ostream &os, const Node &dt);

private:
  T data;
  Node const *next;
};

template <typename T>
ostream &operator << (ostream &os, const Node<T> &dt)
{
  os << dt.data;
  return os;
}

template <typename T>
int circularList (const Node<T> &node)
{
  int pos = 0;
  Node<T> const *fastPtr = node.getNext ()->getNext () ;
  Node<T> const *slowPtr = &node;

  while (fastPtr != slowPtr && fastPtr->endP ())
    {
      fastPtr = fastPtr->getNext ()->getNext ();
      slowPtr = slowPtr->getNext ();
    }

  // This is not a curcular list.
  if (fastPtr->endP ())
    return -1;

  slowPtr = &node;
  while (fastPtr != slowPtr)
    {
      fastPtr = fastPtr->getNext ();
      slowPtr = slowPtr->getNext ();
      pos++;
    }

  cout << *slowPtr << endl;
  return pos;
}


int main ()
{
  Node<char> node1 ('a');
  Node<char> node2 ('b');
  Node<char> node3 ('c');
  Node<char> node4 ('d');
  Node<char> node5 ('e');
  Node<char> node6 ('f');
  Node<char> node7 ('g');

  node1.setNext (node2);
  node2.setNext (node3);
  node3.setNext (node4);
  node4.setNext (node5);
  node5.setNext (node6);
  node7.setNext (node3);

  cout << circularList<char> (node1) << endl;
}
