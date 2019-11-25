#include "Image.h"
#include "cs225/PNG.h"
using namespace std;
using namespace cs225;


void Image::lighten(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(int i=0;(unsigned int)i<hei;i++){
    for(int j=0;(unsigned int)j<wid;j++){
    HSLAPixel &pixel=getPixel(j,i);
    double new_l=pixel.l+0.1;
    if ((new_l>=0) && (new_l<=1))
    pixel.l=new_l;
    if (new_l<0)
    pixel.l=0;
    else if (new_l>1)
    pixel.l=1;
    }
    }
}

void Image::lighten(double amount){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_l=pixel.l+amount;
      if ((new_l>=0) && (new_l<=1))
      pixel.l=new_l;
      if (new_l<0)
      pixel.l=0;
      else if (new_l>1)
      pixel.l=1;
    }
    }
}

void Image::darken(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_l=pixel.l-0.1;
      if ((new_l>=0) && (new_l<=1))
      pixel.l=new_l;
      if (new_l<0)
      pixel.l=0;
      else if (new_l>1)
      pixel.l=1;
    }
    }
}

void Image::darken(double amount){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_l=pixel.l-amount;
      if ((new_l>=0) && (new_l<=1))
      pixel.l=new_l;
      if (new_l<0)
      pixel.l=0;
      else if (new_l>1)
      pixel.l=1;
    }
    }
}

void Image::saturate(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_s=pixel.s+0.1;
      if ((new_s>=0) && (new_s<=1))
      pixel.s=new_s;
    }
    }
}

void Image::saturate(double amount){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_s=pixel.s+amount;
      if ((new_s>=0) && (new_s<=1))
      pixel.s=new_s;
    }
    }
}

void Image::desaturate(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_s=pixel.s-0.1;
      if ((new_s>=0) && (new_s<=1))
      pixel.s=new_s;
    }
    }
}

void Image::desaturate(double amount){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_s=pixel.s-amount;
      if ((new_s>=0) && (new_s<=1))
      pixel.s=new_s;
    }
    }
}

void Image::grayscale(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      pixel.s=0;
    }
    }
}

void Image::illinify(){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      if((pixel.h<113.5)||(pixel.h>293.5)){
        pixel.h=11;                                  //follow illinify rule
      }
      else{
        pixel.h=216;                                 //follow illinify rule
      }
    }
    }
}

void Image::rotateColor(double degrees){
  unsigned int wid= width();
  unsigned int hei= height();
  for(unsigned int i=0;i<hei;i++){
    for(unsigned int j=0;j<wid;j++){
      HSLAPixel &pixel=getPixel(j,i);
      double new_h=pixel.h+degrees;
      if((new_h>=0) && (new_h<=360))
      pixel.h=new_h;
      if(new_h>360){
      int real_h=(int)new_h % 360;
      pixel.h=(double)real_h;
     }
      else if(new_h<0){
      while(new_h<0)
      new_h+=360;
      pixel.h=new_h;
     }
    }
  }
}

void Image::scale(double factor){
Image copy=*this;
unsigned int wid_origin=width();
unsigned int hei_orgin=height();
resize(factor*wid_origin,factor*hei_orgin);
unsigned int wid_new=width();
unsigned int hei_new=height();
for(unsigned int j=0;j<hei_new;j++){
  for(unsigned int i=0;i<wid_new;i++){
    HSLAPixel& pixel=getPixel(i,j);
    HSLAPixel& pixel_copy=copy.getPixel((i/factor),(j/factor));
    pixel=pixel_copy;
  }
}

}
void Image::scale(unsigned int w, unsigned int h){
  Image copy=*this;
  unsigned int wid_origin=width();
  unsigned int hei_orgin=height();
  resize(w*wid_origin,h*hei_orgin);
  unsigned int wid_new=width();
  unsigned int hei_new=height();
  for(unsigned int j=0;j<hei_new;j++){
    for(unsigned int i=0;i<wid_new;i++){
      HSLAPixel& pixel=getPixel(i,j);
      HSLAPixel& pixel_copy=copy.getPixel((i/w),(j/h));
      pixel=pixel_copy;
    }
  }
}
