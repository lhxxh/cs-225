#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  PNG image;
  image.readFromFile(inputFile);               //input the image
  unsigned int width= image.width();
  unsigned int height=image.height();
  int flag=0;
  if(height%2){              //case for odd*odd and odd*even image
    for(unsigned int i=0;i<height;i++){
      for(unsigned int j=0;j<width;j++){       //go through every pixel
        if((j==width/2)&&(i==height/2)){
         flag=1;
         break;                               //if it steps the final one pixel then halt
        }
        HSLAPixel& pixelone=image.getPixel(j,i);
        HSLAPixel& pixeltwo=image.getPixel(width-1-j,height-1-i);
        HSLAPixel pixelres=pixelone;
        pixelone=pixeltwo;
        pixeltwo=pixelres;                   //switch the pixel
      }
      if(flag==1)
      break;
    }
  }
  if(!(height%2)){             //case for even*even and even*odd image
  for(unsigned int i=0;i<height;i++){
    for(unsigned int j=0;j<width;j++){       //step through every pixel
      if(i==height/2){
        flag=1;
        break;                            //if it steps the final one pixel, halt
      }
      HSLAPixel& pixelone=image.getPixel(j,i);
      HSLAPixel& pixeltwo=image.getPixel(width-1-j,height-1-i);
      HSLAPixel pixelres=pixelone;
      pixelone=pixeltwo;
      pixeltwo=pixelres;                        //switch the pixel
    }
    if(flag==1)
    break;
  }
  }
image.writeToFile(outputFile);                 //output the image
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  for(unsigned int j=0;j<height;j++){
    for(unsigned int i=0;i<width;i++){                   //step through the pixel
      HSLAPixel& pixel= png.getPixel(i,j);
      if((i>200)&&(i<600)&&(j>200)&&(j<600)){
        if((i>301)&&(i<499)&&(j>301)&&(j<499)){
          pixel.h=100;
          pixel.l=0.5;
          pixel.s=0.5;
        }
        else{
          pixel.h=216;
          pixel.l=0.5;
          pixel.s=0.5;
          }
        }
      else{
          pixel.h=11;
          pixel.l=0.5;
          pixel.s=0.5;
        }

    }                                            //logic that create three squares in the image
  }


  return png;
}
