#include <iostream>
#include <string>

using namespace std;

int titleToNumber (string str)
{
  int result = 0;

  for (char &c : str)
    {
      if (c < 'A' || c > 'Z')
	{
	  cout << "invalid string: " << str << endl;
	  return 0;
	}
      int val = c - 'A' + 1;
      result = result * 26 + val;
    }

  return result;
}

int main ()
{
  string input;
  cout << "input string: ";
  cin >> input;

  int val = titleToNumber (input);
  cout << val << endl;

  return 0;
}
