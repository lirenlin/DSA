#include <iostream>
#include <thread>
#include <pthread.h>
using namespace std;

pthread_mutex_t lock;
int count = 0;
const int limit = 7;

void thread_do (int id)
{
  bool flag = true;
  while (flag)
    {
      pthread_mutex_lock (&lock);
      if (count % 2 == 0)
	{
	  if (id == 1)
	    {
	      count++;
	      cout << "0";
	    }
	}
      else
	{
	  int remain = count / 2 + 1;
	  if (id == 2 && (remain % 2))
	    {
	      count++;
	      cout << remain;
	    }
	  else if (id == 3 && (remain % 2 == 0))
	    {
	      count++;
	      cout << remain;
	    }
	}

      if (count >= limit)
	flag = false;
      //cout << id << ": " << count << endl;
      pthread_mutex_unlock (&lock);
    }
  return;
}

int main ()
{
  thread t1 (thread_do, 1);
  thread t2 (thread_do, 2);
  thread t3 (thread_do, 3);

  t1.join ();
  t2.join ();
  t3.join ();
  cout << endl;
  return 0;
}
