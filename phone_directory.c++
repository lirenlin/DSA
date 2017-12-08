#include <iostream>
#include <list>
#include <string>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>

using namespace std;
typedef list<string> WordList;
#define ALPHABET_SIZE 26

struct vProperty
{
  string name;
  string color;
};

using namespace boost;
typedef adjacency_list < listS,       // Store out-edges of each vertex in a std::list
	vecS,                       // Store vertex set in a std::vector
	directedS,                  // The graph is directed
	vProperty     // Add a vertex property
	>graph_type;

graph_type::vertex_descriptor createVertex (char c, bool isEndOfWord, graph_type &treeGraph)
{
  vProperty vp;
  vp.name = c;

  if (isEndOfWord)
    vp.color = "red";
  else
    vp.color = "white";

  graph_type::vertex_descriptor vertex = add_vertex(vp, treeGraph);

  return vertex;
}

class TrieNode
{
public:
  TrieNode (bool endOfWord);
  ~TrieNode ();
  void insertNode (TrieNode *node);
  void insertNode (string word);
  TrieNode *searchNode (string word, int &depth);
  WordList getWord (string word);
  bool endOfWord () { return isEndOfWord;}

  void writeGraph (graph_type::vertex_descriptor parentV, graph_type &treeGraph);

private:
  TrieNode *children[ALPHABET_SIZE];
  // If current node is end of word
  bool isEndOfWord;
};

TrieNode::TrieNode (bool endOfWord = false)
{
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    children[i] = nullptr;

  isEndOfWord = endOfWord;
}

TrieNode::~TrieNode ()
{
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
      TrieNode *child = children[i];
      if (child != nullptr)
	delete child;
    }
}

void TrieNode::insertNode (string word)
{
  bool endOfWord = word.length () == 1? true : false;
  char c = tolower (word[0]);
  int idx = c - 97;
  TrieNode *next = children[idx];

  if (next == nullptr)
    {
      next = new TrieNode (endOfWord);
      children[idx] = next;
    }

  if (!endOfWord)
    next->insertNode (word.substr (1));
}

TrieNode *TrieNode::searchNode (string word, int &depth)
{
  if (depth == word.length ())
    return this;

  char c = tolower (word[depth]);
  int idx = c - 97;
  TrieNode *next = children[idx];

  if (next != nullptr)
    return next->searchNode (word, ++depth);
  else
    return this;
}

WordList TrieNode::getWord (string word)
{
  WordList wordList;
  if (isEndOfWord)
    wordList.push_back (word);

  for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
      TrieNode *child = children [i];
      char c= i + 97;
      if (child == nullptr)
	continue;

      WordList subList = child->getWord (word + c);
      for (auto subWord : subList)
	wordList.push_back (subWord);
    }
  return wordList;
};

void TrieNode::writeGraph (graph_type::vertex_descriptor parentV, graph_type &treeGraph)
{
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
      TrieNode *child = children [i];
      char c= i + 97;
      if (child == nullptr)
	continue;
      graph_type::vertex_descriptor newV = createVertex (c, child->endOfWord (), treeGraph);
      add_edge (parentV, newV, treeGraph);
      child->writeGraph (newV, treeGraph);
    }
}

class Book
{
public:
  Book (WordList wordList);
  Book () {}

  void addWord (string word);
  void getSuggestion (string prefix);
  void dumpGraph (graph_type &treeGraph);

private:
  TrieNode root;
};

Book::Book (WordList wordList)
{
  for (string &word : wordList)
      root.insertNode (word);
}

void Book::addWord (string word)
{
  root.insertNode (word);
}

void Book::getSuggestion (string prefix)
{
  int depth = 0;
  TrieNode *node = root.searchNode (prefix, depth);
  WordList wordList = node->getWord ("");
  if (depth == prefix.length ())
    {
      if (node->endOfWord ())
	cout << prefix << endl;
      for (auto word : wordList)
	cout << "\t" << prefix + word << endl;
    }
  else if (depth == 0)
    cout << "no such word in the book: " << prefix << endl;
  else
    {
      cout << "no such word in the book: " << prefix << endl;
      cout << "the cloest words are:" << endl;
      for (auto word : wordList)
	cout << "\t" << prefix.substr (0, depth)  + word << endl;
    }
}

void Book::dumpGraph (graph_type &treeGraph)
{
  graph_type::vertex_descriptor rootV = createVertex ('0', false, treeGraph);
  root.writeGraph (rootV, treeGraph);
}

int main ()
{
  WordList wordList = {"lirenlin", "desk", "arm", "Cambridge", "day",
      "libeibei", "dead", "army"};
  Book book = Book (wordList);

  graph_type treeGraph;
  book.dumpGraph (treeGraph);
  std::ofstream dotfile ("book.dot");

  dynamic_properties dp;
  dp.property ("node_id", get (vertex_index, treeGraph));
  dp.property ("label", get (&vProperty::name, treeGraph));
  dp.property ("color", get (&vProperty::color, treeGraph));


  write_graphviz_dp (dotfile, treeGraph, dp);

  while (true)
    {
      string word;
      cout << "give a word: ";
      cin >> word;

      if (word == "end")
	break;

      book.getSuggestion (word);
    }

  return 0;
}
