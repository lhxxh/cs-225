/* Your code here! */
#ifndef maze_h_
#define maze_h_
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace std;
using namespace cs225;
class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width,int height);
  bool canTravel(int x,int y,int dir)const;
  void setWall(int x,int y,int dir,bool exists);
  vector<int> solveMaze();
  PNG* drawMaze()const;
  PNG* drawMazeWithSolution();
private:
  int width_;
  int height_;
  int size_;
  DisjointSets cells;
  vector<bool> rightwall;
  vector<bool> downwall;
};

#endif
