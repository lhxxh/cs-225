#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
   SquareMaze maze;
   maze.makeMaze(50,50);
   PNG* output=maze.drawMazeWithSolution();
   unsigned Width=output->width();
   unsigned Height=output->height();
   for(unsigned i=0;i<Width/2;i++){
     for(unsigned j=0;j<Height/2;j++){
       HSLAPixel& pixel=output->getPixel(i,j);
       pixel=HSLAPixel(0,1,0,1);
     }
   }
   output->writeToFile("creative.png");
   return 0;
}
