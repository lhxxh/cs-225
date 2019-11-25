#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <iostream>
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y){
  /* @todo [Part 3] */
  if(x>y)
  return HSLAPixel(0,1,0.5);

  return HSLAPixel(increment,1,0.5);
}

MyColorPicker::MyColorPicker(double levelup){
  if(levelup<360)
  increment=levelup;
  else{
    while(levelup>360){levelup-=360;}
    increment=levelup;
  }
}
