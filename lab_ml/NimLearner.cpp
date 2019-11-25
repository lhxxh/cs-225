/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
using std::stringstream;
using std::stoi;
/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    startingVertex_="p1-"+to_string(startingTokens);
    //player 1 vertex
    stringstream ss;
    for(unsigned i=0;i<=startingTokens;i++){
      ss.clear();
      ss.str("");
      ss<<"p1-"<<to_string(i);
      g_.insertVertex(ss.str());
      ss.clear();
      ss.str("");
      ss<<"p2-"<<to_string(i);
      g_.insertVertex(ss.str());
    }
    //first finish 2-step jump
    stringstream ss_source,ss_destination;
    int counter1=startingTokens;
    while(counter1-2>=0){
      int next=counter1-2;
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p1-"<<to_string(counter1);
      ss_destination<<"p2-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p2-"<<to_string(counter1);
      ss_destination<<"p1-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      counter1-=2;
    }
    int counter2=startingTokens-1;
    while (counter2-2>=0) {
      int next=counter2-2;
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p1-"<<to_string(counter2);
      ss_destination<<"p2-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p2-"<<to_string(counter2);
      ss_destination<<"p1-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      counter2-=2;
    }
    //then finish 1-step jump
    int counter3=startingTokens;
    while(counter3-1>=0){
      int next=counter3-1;
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p1-"<<to_string(counter3);
      ss_destination<<"p2-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      ss_source.clear();
      ss_source.str("");
      ss_destination.clear();
      ss_destination.str("");
      ss_source<<"p2-"<<to_string(counter3);
      ss_destination<<"p1-"<<to_string(next);
      g_.insertEdge(ss_source.str(),ss_destination.str());
      g_.setEdgeWeight(ss_source.str(),ss_destination.str(),0);
      counter3-=1;
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 int choosejump=rand()%3;
 int player=1;
 int counter=stoi(startingVertex_.substr(startingVertex_.find("-")+1));
 stringstream ss_source,ss_destination;
 if(counter==0){
   return path;
 }
 else if(counter==1){
   ss_source<<"p1-1";
   ss_destination<<"p2-0";
   path.push_back(g_.getEdge(ss_source.str(),ss_destination.str()));
   return path;
 }
 else{
 while(counter-choosejump>=0){
 if(choosejump>0){
   int next=counter-choosejump;
   ss_source.clear();
   ss_source.str("");
   ss_destination.clear();
   ss_destination.str("");
   if(player==1){
   ss_source<<"p1-"<<to_string(counter);
   ss_destination<<"p2-"<<to_string(next);
   player=2;
 }
  else{
    ss_source<<"p2-"<<to_string(counter);
    ss_destination<<"p1-"<<to_string(next);
    player=1;
  }
   path.push_back(g_.getEdge(ss_source.str(),ss_destination.str()));
   counter=next;
   }
   choosejump=rand()%3;
 }
}
if(counter==0)
  return path;
else{
  ss_source.clear();
  ss_source.str("");
  ss_destination.clear();
  ss_destination.str("");
  if(player==1){
  ss_source<<"p1-1";
  ss_destination<<"p2-0";
  }
  else{
  ss_source<<"p2-1";
  ss_destination<<"p1-0";
  }
  path.push_back(g_.getEdge(ss_source.str(),ss_destination.str()));
  return path;
}

}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 int j;
 if(path[path.size()-1].dest=="p2-0"){
   j=1;
 }
 else{
   j=-1;
 }
 for(size_t i=0;i<path.size();i++){
   int oldweight=path[i].getWeight();
   g_.setEdgeWeight(path[i].source,path[i].dest,oldweight+j);
   j*=-1;
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
