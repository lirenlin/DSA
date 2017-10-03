#include <iostream>
#include <unordered_set>
#include <string>
#include <list>
#include <cstring>

using namespace std;

class Node
{
public:
  Node (string word): word (word) { parent = NULL; }
  Node (string word, Node *parent): word (word), parent (parent) {}
  ~Node ()
    {
      for (auto it = children.begin (); it != children.end (); ++it)
	delete *it;
    }

  void addChild (Node *child) { children.push_back (child); }
  Node *getParent () { return parent; }
  string getWord () { return word; }

  list<Node *> children;
private:
  string word;
  Node *parent;
};

typedef list<Node*> NodeList;
typedef unordered_set <string> Dict;


void findLadder (string beginWord, string endWord, Dict dict)
{
  const char chars [] = "abcdefghijklmnopqrstuvwxyz";
  list<char> characters (chars, chars + strlen (chars));
  int len;

  len = beginWord.size ();
  if (len != endWord.size ())
    cout << "The length doesn't match: " << beginWord << " " << endWord << endl;

  dict.insert (endWord);
  NodeList cur_level;
  cur_level.push_back (new Node (beginWord));
  NodeList next_level;

  NodeList path;
  bool done = false;

  while (!cur_level.empty ())
    {
      for (auto it = cur_level.begin (); it != cur_level.end (); ++it)
	{
	  if ((*it)->getWord () == endWord)
	    {
	      /* keep search at the current level.  */
	      path.push_back (*it);
	      done = true;
	    }

	  for (int i = 0; i < len; i++)
	    {
	      for (auto char_it = characters.begin ();
		   char_it != characters.end (); ++char_it)
		{
		  string tmp = (*it)->getWord ();
		  tmp.replace (i, 1, 1, *char_it);
		  auto word_it = dict.find (tmp);
		  if (word_it != dict.end ())
		    {
		      Node *newNode = new Node (tmp, *it);
		      /* Don't remvoe it from dictionary because we want to
		         match multiple path.  Otherwise, only one path could
			 be found.  */
		      if (tmp != endWord)
			dict.erase (word_it);

		      (*it)->addChild (newNode);
		      next_level.push_back (newNode);
		    }
		}
	    }
	}

      if (done)
	break;

      cur_level = next_level;
      next_level.clear ();

      cout << "current level of candidates: ";
      for (auto it = cur_level.begin (); it != cur_level.end (); ++it)
        cout << (*it)->getWord () << ' ';
      cout << endl;
    }

  Node *node;
  for (auto it = path.begin (); it != path.end (); ++it)
    {
      node = (*it);
      while (node != NULL)
	{
	  cout << node->getWord ();
	  if (node->getParent () == NULL)
	    {
	      break;
	    }
	  else
	    {
	      cout << " <- ";
	      node = node->getParent ();
	    }
	}
      cout << endl;
    }

  /* node current is the root of tree.  */
  delete node;
}

int main ()
{
  string input, target;
  int len;
  Dict dict = {"hot", "dog", "dot", "lot", "log"};

  cout << "enter a start word: ";
  cin >> input;
  cout << "enter a end word: ";
  cin >> target;

  findLadder (input, target, dict);
}
