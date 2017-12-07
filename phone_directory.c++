#include <iostream>
#include <list>
#include <string>

using namespace std;
typedef list<string> WordList;
#define ALPHABET_SIZE 26

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

class Book
{
public:
  Book (WordList wordList);
  Book () {}

  void addWord (string word);
  WordList getSuggestion (string prefix);

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

WordList Book::getSuggestion (string prefix)
{
  int depth = 0;
  TrieNode *node = root.searchNode (prefix, depth);
  if (depth == prefix.length ())
    {
      if (node->endOfWord ())
	cout << prefix << endl;
      WordList wordList = node->getWord ("");
      for (auto word : wordList)
	cout << "\t" << prefix + word << endl;
    }
  else
    cout << "no such word in the book: " << prefix << endl;
}

int main ()
{
  WordList wordList = {"lirenlin", "desk", "arm", "Cambridge", "day",
      "libeibei"};
  Book book = Book (wordList);

  while (true)
    {
      string word;
      cout << "give a word: ";
      //cin >> word;
      word = "li";

      if (word == "end")
	break;

      book.getSuggestion (word);
    }

  return 0;
}
