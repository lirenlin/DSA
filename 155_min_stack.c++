#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
class minStack
{
public:
  minStack (): data_size (0) {};
  T& min () { return min_stack.top ();}

  T& top ();
  void pop ();
  void push (const T &val);
  bool empty () const { return data_size == 0; }
  size_t size () const { return data_size;}

private:
  stack<T, vector<T> > data_stack;
  size_t data_size;

  stack<T, vector<T> > min_stack;
};

template <typename T>
T& minStack<T>::top ()
{
  return data_stack.top ();
}

template <typename T>
void minStack<T>::pop ()
{
  if (!min_stack.empty ())
    {
      T data = data_stack.top ();
      T min_data = min_stack.top ();
      if (data == min_data)
	min_stack.pop ();
    }

  data_stack.pop ();
  data_size--;
}

template <typename T>
void minStack<T>::push (const T &val)
{
  if (min_stack.empty ())
    min_stack.push (val);
  else
    {
      T min_data = min_stack.top ();
      if (val < min_data)
	min_stack.push (val);
    }

  data_stack.push (val);
  data_size++;
}

int main ()
{
  minStack<int> stack;
  stack.push (10);
  stack.push (12);
  stack.push (2);
  stack.push (15);
  stack.push (1);

  cout << stack.min () << endl;
  stack.pop ();
  cout << stack.min () << endl;
  stack.push (0);
  cout << stack.min () << endl;

  return 0;
}
