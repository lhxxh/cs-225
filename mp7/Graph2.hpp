#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <unordered_map>
using std::vector;
using std::stack;
using std::queue;
using std::unordered_map;
using std::pair;
/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
  queue <string> record;
  stack <string> helper;
  unordered_map<string,unordered_map<string,string>> propoerty;
  for(const pair<string,V&>& it:vertexMap){
    propoerty[it.first]["visited"]="false";
    propoerty[it.first]["pred"]="nothing";
  }
  record.push(start);
  while(!record.empty()){
    string popedvertice=record.front();
    propoerty[popedvertice]["visited"]="true";
    list<reference_wrapper<E>> edges=incidentEdges(popedvertice);
    for(const reference_wrapper<E>& it:edges){
      if(it.get().dest().key()==popedvertice&&propoerty[it.get().source().key()]["visited"]=="false"){
        string v_neighbour=it.get().source().key();
        record.push(v_neighbour);
        propoerty[v_neighbour]["pred"]=popedvertice;
        propoerty[v_neighbour]["visited"]="true";
      }
      else if(it.get().source().key()==popedvertice&&propoerty[it.get().dest().key()]["visited"]=="false"){
        string v_neighbour=it.get().dest().key();
        record.push(v_neighbour);
        propoerty[v_neighbour]["pred"]=popedvertice;
        propoerty[v_neighbour]["visited"]="true";
      }
    }
    record.pop();
  }
  string currentvertex=end;
  while(currentvertex!="nothing"){
    helper.push(currentvertex);
    currentvertex=propoerty[currentvertex]["pred"];
  }
  while(!helper.empty()){
    path.push_back(helper.top());
    helper.pop();
  }
  return path;
}
