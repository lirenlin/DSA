#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

double MontePI (int n)
{
  double PI;
  double x, y;
  int i = 0, sum = 0;

  for (i; i < n; ++i)
    {
      x = (double)rand () / RAND_MAX;
      y = (double)rand () / RAND_MAX;

      if ((x * x + y * y) <= 1)
	sum++;
    }

  PI = 4.0 * sum / n;
  return PI;
}
void *thread_func (void *ptr)
{
  double res;
  int n = *(int*)ptr;
  res = MontePI (n);
  printf ("%d points: %f\n", n, res);
}

#define N 10000000
#define N_THREAD 2

void thread_MontePI ()
{
  int i;
  int n[N_THREAD];
  pthread_t threads[N_THREAD];

  for (i = 0; i < N_THREAD; ++i)
    {
      n[i] = N * (i+1);
      if (pthread_create (&threads[i], NULL, thread_func, &n[i]) != 0)
	{
	  printf ("Cannot create thread # %d\n", i);
	  break;
	}
    }

  for (i = 0; i < N_THREAD; ++i)
    if (pthread_join (threads[i], NULL) != 0)
      printf ("Cannot join thread # %d\n", i);
}

void serial_MontePI ()
{
  double res;
  int i, n;
  for (i = 0; i < N_THREAD; ++i)
    {
      n = N * (i+1);
      res = MontePI (n);
      printf ("%d points: %f\n", n, res);
    }
}

void main ()
{
  //serial_MontePI ();
  thread_MontePI ();
}
