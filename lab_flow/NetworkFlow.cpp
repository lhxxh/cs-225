/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Edge> edges=g_.getEdges();
  for(const Edge& it:edges){
    flow_.insertEdge(it.source,it.dest);
    flow_.setEdgeWeight(it.source,it.dest,0);
    residual_.insertEdge(it.source,it.dest);
    residual_.setEdgeWeight(it.source,it.dest,it.getWeight());
    residual_.insertEdge(it.dest,it.source);
    residual_.setEdgeWeight(it.dest,it.source,0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int ret=residual_.getEdge(path[0],path[1]).getWeight();
  for(size_t i=1;i<path.size()-1;i++){
    int edgeweight=residual_.getEdgeWeight(path[i],path[i+1]);
    ret=min(edgeweight,ret);
  }
  return ret;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> path;
  while(findAugmentingPath(source_,sink_,path)){
    int capacity=pathCapacity(path);
    for(size_t i=0;i<path.size()-1;i++){
      residual_.setEdgeWeight(path[i],path[i+1],residual_.getEdgeWeight(path[i],path[i+1])-capacity);
      residual_.setEdgeWeight(path[i+1],path[i],residual_.getEdgeWeight(path[i+1],path[i])+capacity);
      if(!flow_.edgeExists(path[i],path[i+1]))
      flow_.setEdgeWeight(path[i+1],path[i],flow_.getEdgeWeight(path[i+1],path[i])-capacity);
      else
      flow_.setEdgeWeight(path[i],path[i+1],flow_.getEdgeWeight(path[i],path[i+1])+capacity);
    }
    path.clear();
  }
  vector<Edge> f_edges=flow_.getEdges();
  int maxflow=0;
  for(const Edge& it:f_edges){
    if(it.source==source_){
      maxflow+=it.getWeight();
    }
  }
  maxFlow_=maxflow;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
