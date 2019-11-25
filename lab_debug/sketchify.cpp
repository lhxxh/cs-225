#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double hue) {
  HSLAPixel* a=new HSLAPixel(hue, 0.8, 0.5);
  return a;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original=new PNG(100,100);
    cout<<"Reached line 23"<<endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    cout<<"Reached line 27"<<endl;
    // Create out.png
    PNG* output;
    output=setupOutput(width, height);
     cout<<"Reached line 31"<<endl;
    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(11);
     cout<<"Reached line 34"<<endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; (0 < y)&&(y<height) ; y++) {
        for (unsigned x = 1; (0 < x)&&(x< width); x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel& currOutPixel = (*output).getPixel(x, y);
            if (diff > 20) {
                currOutPixel = *myPixel;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}