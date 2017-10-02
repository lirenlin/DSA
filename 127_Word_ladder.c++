#include <iostream>
#include <unordered_set>
#include <string>
#include <list>
#include <cstring>

using namespace std;

int main ()
{

  string input, target;
  int len;
  unordered_set <string> dict = {"hot", "dog", "dot", "lot", "log"};
  const char chars [] = "abcdefghijklmnopqrstuvwxyz";
  list<char> characters (chars, chars + strlen (chars));

  cout << "enter a start word: ";
  cin >> input;
  cout << "enter a end word: ";
  cin >> target;

  len = input.size ();
  if (len != target.size ())
    cout << "The length doesn't match: " << input << " " << target << endl;

  dict.insert (target);
  list <string> cur_level = {input};
  list <string> next_level;
  int depth = 0;
  bool done = false;
  while (!cur_level.empty ())
    {
      for (auto it = cur_level.begin (); it != cur_level.end (); ++it)
	{
	  if (*it == target)
	    {
	      done = true;
	      break;
	    }

	  for (int i = 0; i < len; i++)
	    {
	      for (auto char_it = characters.begin ();
		   char_it != characters.end (); ++char_it)
		{
		  string tmp = *it;
		  tmp.replace (i, 1, 1, *char_it);
		  auto word_it = dict.find (tmp);
		  if (word_it != dict.end ())
		    {
		      dict.erase (word_it);
		      next_level.push_back (tmp);
		    }
		}
	    }
	}

      if (done)
	break;

      depth += 1;
      cur_level = next_level;
      next_level.clear ();

      cout << "level: " << depth << ' ';
      for (auto it = cur_level.begin (); it != cur_level.end (); ++it)
	cout << *it << ' ';
      cout << endl;

    }
  cout << depth << " steps" << endl;
}
