#include <iostream>
using namespace std;

template <typename T, int N> class ListStack;
template <typename T, int N>
ostream & operator << (ostream &os, const ListStack <T, N>& dt);

template <typename T, int N>
class ListStack
{
public:
  explicit ListStack (int size);
  ~ListStack () { delete [] array;};

  bool push (const T& val, int i);
  void pop (int i);
  const T& top (int i) const;

  friend ostream & operator << <T, N> (ostream &os, const ListStack& dt);

private:
  struct Node
    {
      T data;
      int preIdx;
    };

  int topIdx[N];
  Node *array;
  int size;
  int nextIdx;
};
template <typename T, int N>
ListStack <T, N>::ListStack (int size): size (size), nextIdx (0)
{
  // -2 means the node is free.
  array = new Node[size];
  for (int i = 0; i < size; ++i)
    array[i].preIdx = -2;

  // -1 means end of stack
  for (int i = 0; i < N; ++i)
    topIdx[i] = -1;
}

template <typename T, int N>
bool ListStack<T, N>::push (const T& val, int i)
{
  if (nextIdx == size)
    {
      cout << "msg: space is full" << endl;
      return false;
    }

  if (i >= N)
    return false;

  array[nextIdx].data = val;
  array[nextIdx].preIdx = topIdx[i];
  topIdx[i] = nextIdx;

  // find the next slot
  int hasSpace = -1;
  for (int i = nextIdx + 1; i < size; ++i)
    {
      if (array[i].preIdx == -2)
	{
	  hasSpace = i;
	  break;
	}
    }
  nextIdx = (hasSpace != -1)? hasSpace : size;

  return true;
}

template <typename T, int N>
void ListStack<T, N>::pop (int i)
{
  if (i >= N)
    return;

  if (topIdx[i] == -1)
    {
      cout << "msg: stack " << i << " is empty." << endl;
      return;
    }

  nextIdx = topIdx[i];
  // update the current stack head
  topIdx[i] = array[nextIdx].preIdx;

  // clear the data and link.
  array[nextIdx].data = 0;
  array[nextIdx].preIdx = -2;
}

template <typename T, int N>
const T& ListStack<T, N>::top (int i) const
{
  if (i >= N)
    return 0;

  return array[topIdx[i]].data;
}

template <typename T, int N>
ostream & operator << (ostream &os, const ListStack<T, N>& dt)
{
  cout << "Total space: " << dt.size << " shared by " << N << " stack" << endl;
  for (int i = 0; i < N; ++i)
    {
      int idx = dt.topIdx[i];
      if (idx == -1)
	{
	  cout << "stack " << i << ": empty" << endl;
	  continue;
	}
      else
	cout << "stack " << i << ": ";

      while (idx != -1)
	{
	  cout << dt.array[idx].data << " ";
	  idx = dt.array[idx].preIdx;
	}
      cout << endl;
    }
}

int main ()
{
  ListStack<int, 3> listStack (10);

  listStack.push (1, 0);
  listStack.push (2, 0);
  listStack.push (4, 1);
  listStack.push (3, 0);
  listStack.push (5, 1);
  listStack.push (6, 1);
  listStack.push (7, 2);
  listStack.push (8, 2);
  listStack.push (9, 2);
  listStack.push (10, 2);
  listStack.pop (0);
  listStack.push (11, 2);
  listStack.push (11, 2);
  listStack.pop (0);
  listStack.pop (0);
  listStack.pop (0);
  listStack.push (11, 2);
  listStack.push (11, 2);
  listStack.push (11, 2);
  listStack.push (11, 2);

  cout << listStack;
  return 0;
}
