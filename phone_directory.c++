#include <iostream>
#include <list>
#include <string>

using namespace std;

class TrieNode
{
  TrieNode (char cha);
  void insertNode (TrieNode *node);
  void insertNode (string word);

private:
  void setParent (TrieNode *parent);

  TrieNode *children[ALPHABET_SIZE];
  char hold_char;
  // If current node is end of word
  bool isEndOfWord;
};

TrieNode:TrieNode (char cha)
{
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    children[i] = nullptr;

  hold_char = cha;
}

void TrieNode::insertNode (string word)
{
  char c = tolower (word[0]);
  int idx = tolower (c) - 97;
  TrieNode *next = children[idx];

  if (next == nullptr)
    {
      next = New TrieNode (c);
      children[idx] = next;
    }

  next->insertNode (word.substr (1));
}


class book
{
  book (list<string> wordList);
  book ();

  void addWord (string word);
  list<string> getSuggestion (string prefix);


private:
  TrieNode root;
}

book::book (list<string> wordList>)
