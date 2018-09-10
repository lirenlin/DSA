#include <iostream>
#include <vector>
#include <cassert>

//forward declration
template <typename T>
class NodeFactory;
template <typename T>
class Node;
template <typename T>
std::ostream & operator << (std::ostream &os, const Node <T>& dt);

template <typename T>
using CL = std::vector<Node<T> *>;

template <typename T>
class Node
{
  friend class NodeFactory<T>;
  friend std::ostream & operator << <T> (std::ostream &os, const Node& dt);

public:
  unsigned order = 0;
  void addChild (Node *child) {childrenList.push_back (child);}

  Node *getParent () const {return parent;}
  CL<T> &getChildren () const {return childrenList;}
  T getVal () const {return val;};
  unsigned getChildrenNum() const {return childrenList.size();}
  Node<T> *getNthChild(unsigned n)
    {
      assert (n < childrenList.size());
      return childrenList[n];
    }

  void dump () const
    {
      std::cout << val << '\n';
    }

  std::ostream &dump (std::ostream &os, unsigned depth) const
    {
      for (unsigned i = 0; i < depth; ++i)
	os << ' ';
      os << val << '\n';
      for (auto Itr : childrenList)
	Itr->dump (os, depth+1);
      return os;
    }

  void dumpGraph (std::string title) const
    {
      std::cout << "digraph \"" << title << "\" {" << '\n';
      dumpDot ();
      std::cout << "}" << '\n';
    }

  void dumpDot () const
    {
      std::cout << "Node" << this << " [label=\"" << order << ": " << val << "\"];\n";
      for (auto Itr : childrenList)
	{
	  std::cout << "Node" << this << " -> Node" << Itr << ";\n";
	  Itr->dumpDot ();
	}
    }

  protected:
  // can only be created by factory class
  Node (T val): val (val) {};

private:
  const T val = {};
  CL<T> childrenList;
  Node *parent;
};

template <typename T>
std::ostream &operator << (std::ostream &os, const Node<T> &node) {
    node.dump (os, 0);
}

template <typename T>
class NodeFactory
{
public:
  NodeFactory () {};
  ~NodeFactory ();
  Node<T> *makeNode (T val);

private:
  CL<T> nodeList;
};

template <typename T>
NodeFactory<T>::~NodeFactory()
{
  for (auto *Iter: nodeList)
    delete Iter;
}

template <typename T>
Node<T> *NodeFactory<T>::makeNode(T val)
{
  Node<T> *node = new Node<T>(val);
  nodeList.push_back (node);
  return node;
}

template <typename T>
CL<T> postOrder (Node<T> *root)
{
  CL<T> result;
  using meta = std::pair<Node<T> *, unsigned>;
  std::vector<meta> stack;
  stack.push_back (std::make_pair (root, 0));
  while (!stack.empty())
    {
      Node<T> *node = (stack.back ()).first;
      unsigned idx = (stack.back ()).second++;

      // this is a leaf node
      if (0 == node->getChildrenNum ())
	{
	  result.push_back (node);
	  stack.pop_back ();
	}
      else
	{
	  // finished visiting all the children
	  if (idx == node->getChildrenNum ())
	    {
	      result.push_back (node);
	      stack.pop_back ();
	    }
	  // otherwise, visit next child
	  else
	    {
	      Node<T> *child = node->getNthChild (idx);
	      stack.push_back (std::make_pair (child, 0));
	    }
	}
    }
  return result;
}

template <typename T>
CL<T> preOrder (Node<T> *root)
{
  CL<T> result;
  using meta = std::pair<Node<T> *, unsigned>;
  std::vector<meta> stack;
  stack.push_back (std::make_pair (root, 0));
  while (!stack.empty())
    {
      Node<T> *node = (stack.back ()).first;
      unsigned idx = (stack.back ()).second++;

      if (idx == 0)
	result.push_back (node);

      // this is a leaf node, or we finished visiting all the child nodes
      if (0 == node->getChildrenNum () || idx == node->getChildrenNum ())
	stack.pop_back ();
      else
	{
	  Node<T> *child = node->getNthChild (idx);
	  stack.push_back (std::make_pair (child, 0));
	}
    }
  return result;
}

template <typename T>
CL<T> inOrder (Node<T> *root)
{
  CL<T> result;
  using meta = std::pair<Node<T> *, unsigned>;
  std::vector<meta> stack;
  stack.push_back (std::make_pair (root, 0));
  while (!stack.empty())
    {
      Node<T> *node = (stack.back ()).first;
      unsigned idx = (stack.back ()).second++;

      // this is a leaf node
      if (0 == node->getChildrenNum ())
	{
	  result.push_back (node);
	  stack.pop_back ();
	  continue;
	}

      if (idx == 1)
	result.push_back (node);

      // finished visiting all the child nodes
      if (idx == node->getChildrenNum ())
	stack.pop_back ();
      else
	{
	  Node<T> *child = node->getNthChild (idx);
	  stack.push_back (std::make_pair (child, 0));
	}
    }
  return result;
}

int main ()
{
  NodeFactory<char> ctx = {};
  Node<char> *root = ctx.makeNode('a');
  Node<char> *node2 = ctx.makeNode('b');
  Node<char> *node3 = ctx.makeNode('c');
  Node<char> *node4 = ctx.makeNode('d');
  Node<char> *node5 = ctx.makeNode('e');
  Node<char> *node6 = ctx.makeNode('f');
  Node<char> *node7 = ctx.makeNode('g');
  Node<char> *node8 = ctx.makeNode('h');
  Node<char> *node9 = ctx.makeNode('i');
  Node<char> *node10 = ctx.makeNode('j');

  root->addChild (node2);
  root->addChild (node3);
  root->addChild (node9);
  node2->addChild (node4);
  node2->addChild (node5);
  node5->addChild (node6);
  node5->addChild (node7);
  node5->addChild (node8);
  node4->addChild (node10);

  root->dumpGraph ("org");

  CL<char> result = postOrder (root);
  unsigned idx = 0;
  for (int i = 0; i < result.size (); ++i)
    result[i]->order = i;
  root->dumpGraph ("PostOrder");

  result = preOrder (root);
  for (int i = 0; i < result.size (); ++i)
    result[i]->order = i;
  root->dumpGraph ("PreOrder");

  result = inOrder (root);
  for (int i = 0; i < result.size (); ++i)
    result[i]->order = i;
  root->dumpGraph ("Inorder");

  return 0;
}
