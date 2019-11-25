
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;      png.readFromFile("tests/pacman.png");

  FloodFilledImage prepare(png);
  Point start(100,100);
  DFS firstmethod(png,start,0.2);
  MyColorPicker firstpicker(180.0);
  BFS secondmethod(png,start,0.2);
  MyColorPicker secondpicker(90.0);

  prepare.addFloodFill(firstmethod,firstpicker);
  Animation animate=prepare.animate(1000);
  PNG lastFrame=animate.getFrame(animate.frameCount()-1);
  lastFrame.writeToFile("myFloodFill.png");
  animate.write("myFloodFill.gif");

  prepare.addFloodFill(secondmethod,secondpicker);
  Animation animate2=prepare.animate(1000);
  PNG lastFrame2=animate2.getFrame(animate2.frameCount()-1);
  lastFrame2.writeToFile("myFloodFill.png");
  animate2.write("myFloodFill.gif");
  return 0;
}
