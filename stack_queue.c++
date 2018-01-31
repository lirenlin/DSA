#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

template <typename T> class Queue;
template <typename T>
ostream & operator << (ostream &os, Queue <T>& dt);

template <typename T>
class Queue
{
public:
  Queue (): sz (0) {};

  void pop ();
  void push (const T&val);

  T& front ();
  const T& front () const;

  size_t size () const {return sz;};
  bool empty () const { return sz != 0;};
  friend ostream & operator << <T> (ostream &os, Queue& dt);
private:
  stack<T> inputStack;
  stack<T> outputStack;
  size_t sz;

  void move ();
};

template <typename T>
void Queue<T>::pop ()
{
  if (sz == 0)
    return;

  if (outputStack.empty ())
    move ();

  outputStack.pop ();
  sz--;
}

template <typename T>
void Queue<T>::push (const T&val)
{
  inputStack.push (val);
  sz++;
}

template <typename T>
T& Queue<T>::front ()
{
  if (sz == 0)
    throw logic_error ("front on empty queue");

  if (outputStack.empty ())
    move ();

  T item = outputStack.top ();
  return item;
}

template <typename T>
const T& Queue<T>::front () const
{
  if (sz == 0)
    throw logic_error ("front on empty queue");

  if (outputStack.empty ())
    move ();

  const T item = outputStack.top ();
  return item;
}
template <typename T>
void Queue<T>::move ()
{
  while (!inputStack.empty ())
    {
      outputStack.push (inputStack.top ());
      inputStack.pop ();
    }
}

template <typename T>
ostream & operator << (ostream &os, Queue<T>& dt)
{
  while (!dt.empty ())
    {
      cout << dt.front () << " ";
      dt.pop ();
    }
}

int main ()
{
  Queue<int> queue;
  queue.push (1);
  queue.push (2);
  queue.push (3);
  queue.push (4);
  queue.push (5);
  queue.push (6);
  queue.pop ();
  queue.push (7);

  cout << queue << endl;
}
