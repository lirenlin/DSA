//namespace to hide details
//using keyword
//bk tree;
//edit distance, DP
//template
//functor
//map vector

#include <iostream>
#include <map>
#include <vector>

namespace detail
{
  template <typename KeyType, typename MetricType, typename Distance>
    class tree_node
      {
    public:
      using NodeType = tree_node<KeyType, MetricType, Distance>;
      using ChildrenMapTy = std::map<MetricType, NodeType *>;
      using ResultTy = std::vector<std::pair<KeyType, MetricType>>;
    private:
      KeyType value;
      ChildrenMapTy *children;
      Distance d;

    public:
      tree_node (const KeyType &key): value (key), children (nullptr) {}
      ~tree_node ()
	{
	  if (children)
	    {
	      for (auto iter = children->begin (); iter != children->end (); ++iter)
		delete iter->second;
	      delete children;
	    }
	}

      bool insert (NodeType *node)
	{
	  if (!node)
	    return false;

	  MetricType distance = d (node->value, this->value);
	  if (distance == 0)
	    return false;

	  if (!children)
	    children = new ChildrenMapTy ();

	  auto iter = children->find (distance);
	  // No child with this distance, insert a new one
	  if (iter == children->end ())
	    {
	      children->insert (std::make_pair (distance, node));
	      return true;
	    }
	  // otherwise, add it to the child with the same distance
	  return iter->second->insert (node);
	}

      ResultTy find_nodes (const KeyType &key, MetricType limit) const
	{
	  ResultTy result;
	  find_nodes (result, key, limit);
	  return result;
	}

      void dump_tree (int depth = 0)
	{
	  for (int i = 0; i < depth; ++i)
	    std::cout << "\t";
	  std::cout << this->value << std::endl;
	  if (this->has_children ())
	    for (auto iter = children->begin (); iter != children->end ();
		 ++iter)
	      iter->second->dump_tree (depth + 1);
	}


    private:
      bool has_children () const
	{
	  return this->children && this->children->size ();
	}

      void find_nodes (ResultTy &result, const KeyType &key, MetricType limit) const
	{
	  MetricType n = d (key, this->value);
	  if (n <= limit)
	    result.emplace_back (this->value, n);

	  if (!this->has_children ())
	    return;

	  for (auto iter = children->begin (); iter != children->end (); ++ iter)
	    {
	      MetricType distance = iter->first;
	      if (n - limit <= distance && distance <= n + limit)
		iter->second->find_nodes (result, key, limit);
	    }

	}
      };
}

struct levenshtein_distance
{
  int min (int a, int b, int c) const
    {
      int tmp = a > b? b : a;
      return (tmp > c? c: tmp);
    }

  int operator () (const std::string &str1, const std::string &str2) const
    {

      int size1 = str1.size ();
      int size2 = str2.size ();

      int dp[size1+1][size2+1];

      for (int i = 0; i <= size1; i++)
	for (int j = 0; j <= size2; j++)
	  {
	    if (i == 0)
	      dp[i][j] = j;
	    else if (j == 0)
	      dp[i][j] = i;
	    else if (str1[i] == str2[j])
	      dp[i][j]= dp[i-1][j-1];
	    else
	      dp[i][j] = 1 + min (dp[i-1][j],	// remove
				  dp[i][j-1],	// insert
				  dp[i-1][j-1]);	// replace
	  }

      return dp[size1][size2];
    }
};

template <typename KeyType, typename MetricType, typename Distance>
class BKTree
{
private:
  using NodeType = detail::tree_node<KeyType, MetricType, Distance>;
  using ResultTy = std::vector<std::pair<KeyType, MetricType>>;
  NodeType *m_root;
  size_t m_n_nodes;
public:
  BKTree (): m_root (nullptr), m_n_nodes (0) {}
  ~BKTree ()
    {
      if (m_n_nodes)
	delete m_root;
    }

  void insert (const KeyType &key)
    {
      NodeType *node = new NodeType (key);
      if (!m_root)
	{
	  m_root = node;
	  m_n_nodes = 1;
	  return;
	}
      if (m_root->insert (node))
	++m_n_nodes;
    }

  ResultTy find_within (const KeyType &key, MetricType limit) const
    {
      return m_root->find_nodes (key, limit);
    }

  void dump_tree () { m_root->dump_tree(); }

  size_t size () const { return m_n_nodes; }
};

int main ()
{
  BKTree<std::string, int, levenshtein_distance> dic;

  dic.insert ("class");
  dic.insert("cross");
  dic.insert("klass");
  dic.insert("clause");
  dic.insert("close");
  dic.insert("closet");
  dic.insert("grass");
  dic.insert("glass");
  dic.insert("grape");
  dic.insert("grab");
  dic.insert("glob");
  dic.insert("global");
  dic.dump_tree ();

  while (!std::cin.eof()) {
      std::string query;
      std::cin >> query;
      if (query.empty())
	continue;
      auto result = dic.find_within(query, 2.0);
      std::cout << "--- candidates ---" << std::endl;
      for (auto iter = result.begin(); iter != result.end(); ++iter)
	std::cerr << iter->first << "(distance:" << iter->second << ")" << std::endl;
      std::cout << "------------------" << std::endl;
  }

  return 0;
}
