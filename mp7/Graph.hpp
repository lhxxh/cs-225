#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include <iterator>
using std::pair;
using std::list;
using std::unordered_map;
using std::string;
using std::reference_wrapper;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  V v1("test1");
  V v2("test2");
  E e(v1,v2);
  bool judgedirected=e.directed();

  string vertexname="";
  for(const pair<string,V&>& it:vertexMap){
    if(it.second==v){
      vertexname=it.first;
      break;
    }
  }
  if(vertexname==""&&judgedirected==false)
  return 0;
  else if(vertexname==""&&judgedirected==true){
    unsigned int counter=0;
    for(const pair<string,list<edgeListIter>>& it:adjList){
      for(const edgeListIter& it2:it.second){
        if(it2->get().dest()==v){counter+=1;}
      }
    }
    return counter;
  }
  else if(vertexname!=""&&judgedirected==false){
    typename unordered_map<string,list<edgeListIter>>::iterator it=adjList.find(vertexname);
    return it->second.size();
  }
  else{
    unsigned int counter=0;
    for(const pair<string,list<edgeListIter>>& it:adjList){
      for(const edgeListIter& it2:it.second){
        if(it2->get().dest()==v||it2->get().source()==v){counter+=1;}
      }
    }
    return counter;
  }
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  if(vertexMap.find(key)!=vertexMap.end()){
    return vertexMap.find(key)->second;
  }
  V & v=*(new V(key));
  vertexMap.insert(pair<string,V&>(key,v));
  adjList.insert(pair<string,list<edgeListIter>>(key,list<edgeListIter>()));
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  if(vertexMap.find(key)==vertexMap.end())
  return;

    vertexMap.erase(key);
    for(typename unordered_map<std::string, std::list<edgeListIter>>::iterator it=adjList.begin();it!=adjList.end();++it){
      typename list<edgeListIter>::const_iterator it2=it->second.begin();
      while(it2!=it->second.end()){
        if((*it2)->get().dest().key()==key||(*it2)->get().source().key()==key){
          edgeList.erase(*it2);
          it2=it->second.erase(it2);
        }
        else{
          ++it2;
        }
      }
    }
    adjList.erase(key);

  return;
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  // bool judgedirected=e.directed();
  reference_wrapper<E> newedge(e);
  edgeList.push_back(newedge);
  typename list<E_byRef>::iterator it=edgeList.end();
  --it;
  // if(judgedirected==true){
  adjList.find(v1.key())->second.push_back(it);
  // }
  // else{
  // adjList.find(v1.key())->second.push_back(it);
  // E& e_same=(*new E(v2,v1));
  // reference_wrapper<E> newedge_same(e_same);
  // edgeList.push_back(newedge_same);
  // ++it;
  // adjList.find(v2.key())->second.push_back(it);
  // }

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  V v1("test1");
  V v2("test2");
  E e(v1,v2);
  bool judgedirected=e.directed();
  for( typename list<edgeListIter>::const_iterator it=(adjList.find(key1)->second).begin();it!=(adjList.find(key1)->second).end();++it){
    if((*it)->get().source().key()==key1&&(*it)->get().dest().key()==key2){
      edgeList.erase(*it);
      (adjList.find(key1)->second).erase(it);
      break;
    }
  }
  if(judgedirected==true){
    return;
  }
  else{
    for(typename list<edgeListIter>::const_iterator it=(adjList.find(key2)->second).begin();it!=(adjList.find(key2)->second).end();++it){
      if((*it)->get().source().key()==key2&&(*it)->get().dest().key()==key1){
        edgeList.erase(*it);
        (adjList.find(key2)->second).erase(it);
        break;
      }
    }
    return;
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  removeEdge(it->get().source().key(),it->get().dest().key());
  return;
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for(const pair<string,list<edgeListIter>>& it:adjList){
  for(const edgeListIter& it2:it.second){
    if(it2->get().directed()){
      if(it2->get().source().key()==key){edges.push_back(*it2);}
    }
    else{
      if(it2->get().dest().key()==key||it2->get().source().key()==key){edges.push_back(*it2);}
    }
  }
}
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if(adjList.find(key1)->second.size()<adjList.find(key2)->second.size()){
    for(const edgeListIter& it:adjList.find(key1)->second){
      if(it->get().dest().key()==key2){return true;}
    }
    return false;
  }
  else{
    for(const edgeListIter& it:adjList.find(key2)->second){
      if(it->get().dest().key()==key1){return true;}
    }
    return true;
  }
}
