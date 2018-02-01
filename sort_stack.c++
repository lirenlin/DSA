#include <iostream>
#include <stack>

using namespace std;

template <typename T>
stack<T> sortStack (stack<T> input)
{
  stack<T> result;

  while (!input.empty ())
    {
      T val = input.top ();
      input.pop ();

      while (!result.empty () && val < result.top ())
	{
	  input.push (result.top ());
	  result.pop ();
	}
      result.push (val);
    }

  return result;
}

int main ()
{
  stack<int> input;
  input.push (9);
  input.push (8);
  input.push (7);
  input.push (6);
  input.push (5);
  input.push (4);
  input.push (3);
  input.push (2);
  input.push (1);

  stack <int> tmp = input;
  stack <int> result = sortStack<int> (input);

  while (!tmp.empty ())
    {
      auto val = tmp.top ();
      cout << val << " ";
      tmp.pop ();
    }
  cout << endl;

  while (!result.empty ())
    {
      auto val = result.top ();
      cout << val << " ";
      result.pop ();
    }
  cout << endl;

}
