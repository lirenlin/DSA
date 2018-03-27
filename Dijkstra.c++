#include <iostream>
#include <limits>
using namespace std;

constexpr int INF = numeric_limits<int>::max ();
constexpr int vertex = 6;

void
dijkstra (int edges[vertex][vertex], int size, int start)
{
  int distance[size];
  int nodes[size];

  for (int i = 0; i < size; ++i)
    {
      nodes[i] = 0;
      distance[i] = edges[start][i];
    }
  nodes[start] = 1;
  distance[start] = 0;

  for (int i = 0; i < size; ++i)
    {
      if (i == start)
	continue;

      // Find the closed node to the start node.
      int min = INF;
      int next = start;
      for (int j  = 0; j < size; ++j)
	{
	  if (nodes[j] == 0 && distance[j] < min)
	    {
	      next = j;
	      min = distance[j];
	    }
	}
      nodes[next] = 1;
      distance[next] = min;

      // Update the distance with new node
      for (int j = 0; j < size; ++j)
	{
	  if (j == start)
	    continue;

	  // There is a path via new node
	  if (edges[next][j] != INF)
	    {
	      int val = min + edges[next][j];
	      if (distance[j] > val)
		distance[j] = val;
	    }
	}
    }
  for (int i = 0; i < size; ++i)
    cout << distance[i] << " ";
  cout << endl;

}

int
main ()
{
  int v = 5;

  int edges[vertex][vertex] = {
	{0, 1, 12, INF, INF, INF},
	{INF, 0, 9, 3, 13, INF},
	{INF, INF, 0, INF, 5, INF},
	{INF, INF, 4, 0, 13, 15},
	{INF, INF, INF, INF, 0, 4},
	{INF, INF, INF, INF, INF, 0}};

  dijkstra (edges, vertex, 0);
  return 0;
}
