from collections import defaultdict
class Graph:
  def __init__ (self):
    self.nodes = set ()
    self.edges = defaultdict (list)
    self.distance = dict ()

  def add_node (self, node):
    self.nodes.add (node)

  def add_edge_si (self, from_node, to_node, distance):
    self.edges[from_node].append (to_node)
    self.distance[(from_node, to_node)] = distance

  def add_edge_bi (self, node1, node2, distance):
    self.add_edge_si (node1, node2, distance)
    self.add_edge_si (node2, node1, distance)

  def dijkstra_solver (self, init_node):
    if init_node not in self.nodes:
      print "node %s not in the graph: " % init_node, self.nodes
      return None

    visited_nodes = {init_node: 0}
    path = defaultdict (list)
    nodes = set (self.nodes)
    nodes.remove (init_node)

    while nodes:
      for node in nodes:
	min_distance = None
	min_node = None
	#if we havn't visit it before, add it to visited.
	if node not in visited_nodes:
	  edge = (init_node, node)
	  if edge in self.distance:
	    #add node if it's directly connected to start node
	    min_distance = self.distance[(init_node, node)]
	  #add node if it's connected to start node via other nodes
	  for inter_node in visited_nodes:
	    edge = (inter_node, node)
	    if edge in self.distance:
	      new_distance = self.distance[edge] + visited_nodes[inter_node]
	      if min_distance is None:
		min_distance = new_distance
		path[node] = path[inter_node] + [inter_node]
	      elif min_distance > new_distance:
		min_distance = new_distance
		path[node] = path[inter_node] + [inter_node]

	#if we visited it before, update it's shorted distance to init_node
        else: 
	  min_distance = visited_nodes[node]
	  for inter_node in visited_nodes:
	    edge = (inter_node, node)
	    if edge in self.distance:
	      new_distance = self.distance[edge] + visited_nodes[inter_node]
	      if min_distance > new_distance:
		min_distance = new_distance
		path[node] = path[inter_node] + [inter_node]

	if min_distance is not None:
	  visited_nodes[node] = min_distance

      min_node = None
      # find the node with the shorted distance from init_node
      for node in visited_nodes:
        if node == init_node:
          continue
	if node not in nodes:
	    continue
        if min_node is None:
          min_node = node
        else:
          if visited_nodes[min_node] > visited_nodes[node]:
            min_node = node
      # remove it from nodes
      if min_node is not None:
	nodes.remove (min_node) 

    print visited_nodes
    print path

graph = Graph ()
graph.add_node ('A')
graph.add_node ('B')
graph.add_node ('C')
graph.add_node ('D')
graph.add_node ('E')
graph.add_node ('F')
graph.add_node ('G')
graph.add_edge_bi ('A', 'B', 2)
graph.add_edge_bi ('A', 'D', 1)
graph.add_edge_bi ('D', 'B', 2)
graph.add_edge_bi ('D', 'E', 1)
graph.add_edge_bi ('D', 'C', 3)
graph.add_edge_bi ('B', 'C', 3)
graph.add_edge_bi ('C', 'E', 1)
graph.add_edge_bi ('C', 'F', 5)
graph.add_edge_bi ('E', 'F', 2)
graph.add_edge_bi ('E', 'F', 2)
graph.add_edge_bi ('F', 'G', 1)

graph.dijkstra_solver ('A')
