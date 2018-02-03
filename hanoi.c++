#include <iostream>
#include <vector>

using namespace std;


template <typename T>
void hanoi (vector<T> &first, vector<T> &second, vector<T> &last, int n)
{
  if (n == 1)
    {
      T val = first.back ();
      first.pop_back ();
      last.push_back (val);
      return;
    }

  hanoi (first, last, second, n - 1);
  T val = first.back ();
  first.pop_back ();
  last.push_back (val);
  hanoi (second, first, last, n - 1);
}

int main ()
{
  vector<int> first;
  vector<int> second;
  vector<int> last;
  first.push_back (5);
  first.push_back (4);
  first.push_back (3);
  first.push_back (2);
  first.push_back (1);

  for (const auto &val: first)
    cout << val << " ";
  cout << endl;

  hanoi<int> (first, second, last, first.size ());

  for (const auto &val: first)
    cout << val << " ";
  cout << endl;

  for (const auto &val: second)
    cout << val << " ";
  cout << endl;

  for (const auto &val: last)
    cout << val << " ";
  cout << endl;

  return 1;
}
