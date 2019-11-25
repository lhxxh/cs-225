#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

bool ImageTraversal::Iterator::hasnotvisited(const Point& point){
  if(visited[point.y*picture.width()+point.x]==false)
  return true;

  return false;
}

bool ImageTraversal::Iterator::pushallowed(const Point& point){
if(point.x>=picture.width()||point.y>=picture.height())
return false;

const HSLAPixel& pointpixel=picture.getPixel(point.x,point.y);
const HSLAPixel& headpixel=picture.getPixel(head.x,head.y);

if(calculateDelta(headpixel,pointpixel)>=tol)
return false;

return true;

}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal,Point start,double tolerance,PNG pic){
  picture=pic;
  tol=tolerance;
  methodptr=traversal;
  head=start;
  current=head;

  for(unsigned i=0;i<picture.width()*picture.height();i++){
    visited.push_back(false);
  }
  endsignal=false;

  Point right(head.x+1,head.y);
  Point down(head.x,head.y+1);
  Point left(head.x-1,head.y);
  Point up(head.x,head.y-1);

  if(pushallowed(right)==true&&hasnotvisited(right)==true){methodptr->add(right);}
  if(pushallowed(down)==true&&hasnotvisited(down)==true){methodptr->add(down);}
  if(pushallowed(left)==true&&hasnotvisited(left)==true){methodptr->add(left);}
  if(pushallowed(up)==true&&hasnotvisited(up)==true){methodptr->add(up);}

  visited[current.y*picture.width()+current.x]=true;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
  /** @todo [Part 1] */
  methodptr=nullptr;
  endsignal=true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
if(methodptr->empty()==1){endsignal=true;return *this;}

Point nextpoint=methodptr->peek();
while(hasnotvisited(nextpoint)==false){

  if(methodptr->empty()==0)
  nextpoint=methodptr->pop();

  else
  break;
}

if(methodptr->empty()==1&&hasnotvisited(nextpoint)==false){endsignal=true;return *this;}

  Point right(nextpoint.x+1,nextpoint.y);
  Point down(nextpoint.x,nextpoint.y+1);
  Point left(nextpoint.x-1,nextpoint.y);
  Point up(nextpoint.x,nextpoint.y-1);


  if(pushallowed(right)==true&&hasnotvisited(right)==true){methodptr->add(right);}
  if(pushallowed(down)==true&&hasnotvisited(down)==true){methodptr->add(down);}
  if(pushallowed(left)==true&&hasnotvisited(left)==true){methodptr->add(left);}
  if(pushallowed(up)==true&&hasnotvisited(up)==true){methodptr->add(up);}

  current=nextpoint;

  visited[current.y*picture.width()+current.x]=true;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->endsignal==other.endsignal)
  return false;

  return true;

}

ImageTraversal::Iterator::~Iterator(){
  delete methodptr;
  visited.clear();
}

ImageTraversal::~ImageTraversal(){}
