#include <iostream>
#include <list>
using namespace std;

void convert (int num)
{
  char table[26];
  list <char> output;

  for (int i = 0; i < 26; ++i)
    table[i] = 'A' + i;

  if (num == 0)
    {
      cout << "invalid number: 0" << endl;
      return;
    }
  else if (num <= 27)
    {
      cout << num << " --> " << table[num-1] << endl;
      return;
    }

  int tmp = num;
  while (tmp)
    {
      int i = tmp % 26;
      output.push_back (table[i-1]);
      tmp = tmp / 26;
    }

  cout << num << " --> ";
  for (list<char>::reverse_iterator i = output.rbegin();
       i != output.rend(); ++i )
    cout << *i;
  cout << endl;
}

int main ()
{
  convert (26 + 2);
  convert (26*26 + 26 + 2);

  return 0;
}
