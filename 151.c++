#include <iostream>
#include <string>

using namespace std;

void reverse (string &str, unsigned i, unsigned j)
{
  while (i < j)
    {
      char tmp = str[j];
      str[j] = str[i];
      str[i] = tmp;
      i++;
      j--;
    }
}

/* Remove redundant space.  */
string trimString (string str)
{
  int i = 0, j = 1;
  unsigned size = str.size ();
  while (j < size)
    {
      if (str[j] == ' ')
	{
	  reverse(str, i, j - 1);
	  i = j + 1;
	  j += 2;
	}
      else if (j == size - 1)
	{
	  reverse(str, i, j);
	  break;
	}
      else
	++j;
    }

  reverse (str, 0, size - 1);
  return str;
}

int main ()
{
  string str;
  cout << "give a string: ";
  getline (std::cin, str);
  cout << trimString (str) << '\n';
}
