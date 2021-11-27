#include <iostream>
#include <cassert>
#include <limits>
#include <tgmath.h>
#include <cmath>
#include <vector>
#include "seam.h"

// ***********************************
// TASK 1: COLOR
// ***********************************

int digit_counter(const int& num) {
  // function to count the number of digits in an integer that will be used
  // in the function to convert from binary to decimal
  bool flag(true);
  int digits(0), i(1);
  while(flag) {
    if(num/pow(10, i) < 1) {
      digits = i;
      flag = false;
    } else {
      ++i;
    }
  }
  return digits;
}
// Added function to convert from binary to decimal
int binary_to_decimal(const int& bin) {
  int temp(0), decimal(0);
  int digits = digit_counter(bin);
  for(int i(0); i < digits; ++i) {
    temp = bin >> i;
    if((temp & 0b1) == 1) {
      decimal += pow(2, i);
    }
  }
  return decimal;
}

int decimal_to_binary(const int& dec) { // NOT FINISHED!!
  int bin(0), copy(dec), remainder(0);
  do {
    remainder = copy % 2;
    if(remainder == 1) {
      copy = (copy - 1)/2;
      bin = bin*10 + 1;
    } else {
      copy = copy/2;
      bin *= 10;
    }
    if(copy == 1) {
      bin = bin*10 + 1;
    }
  } while(copy != 0);
  return bin;
}

// Returns red component (in the scale 0.0-1.0) from given RGB color.
double get_red(int rgb)
{
    double red_component(.0);
    int r = rgb >> 16;
    r = r & 0b11111111;
    // to be completed ...
    red_component = binary_to_decimal(r)/255.0;
    return red_component;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb)
{
    return 0.; // TODO MODIFY AND COMPLETE
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb)
{
    return 0.; // TODO COMPLETE AND MODIFY
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb)
{
    return 0; // TODO MODIFY AND COMPLETE
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue)
{

    return 0; // TODO MODIFY AND COMPLETE
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray)
{
    return 0; // TODO MODIFY AND COMPLETE
}

// Converts  RGB image to grayscale double image.
GrayImage to_gray(const RGBImage &cimage)
{

    return {}; // TODO MODIFY AND COMPLETE
}

// Converts grayscale double image to an RGB image.
RGBImage to_RGB(const GrayImage &gimage)
{

    return {}; // TODO MODIFY AND COMPLETE
}

// ***********************************
// TASK 2: FILTER
// ***********************************

// Get a pixel without accessing out of bounds
// return nearest valid pixel color
void clamp(long &val, long max)
{
    // TODO : COMPLETE
}

// Convolve a single-channel image with the given kernel.
GrayImage filter(const GrayImage &gray, const Kernel &kernel)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Smooth a single-channel image
GrayImage smooth(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute horizontal Sobel filter

GrayImage sobelX(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute vertical Sobel filter

GrayImage sobelY(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute the magnitude of combined Sobel filters

GrayImage sobel(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// ************************************
// TASK 3: SEAM
// ************************************

Graph create_graph(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Return shortest path from Node from to Node to
// The path does NOT include the from and to Node
Path shortest_path(Graph &graph, size_t from, size_t to)
{

    return {}; // TODO MODIFY AND COMPLETE
};

Path find_seam(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// ***********************************
// TASK 3 provided functions
// Highlight or remove seam from RGB or gray image
// ***********************************

// Draw a seam on a gray image
// return a new gray image with the seam in black
GrayImage highlight_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    // Paint seam in black
    for (size_t row(0); row < seam.size(); ++row) {
        result[row][seam[row]] = 0;
    }
    return result;
}

// Draw a seam on an RGB image
// return a new RGB image with the seam in blue
RGBImage highlight_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    // Paint seam in blue
    for (size_t row(0); row < seam.size(); ++row) {
        result[row][seam[row]] = 0x000ff;
    }
    return result;
}

// Remove specified seam from a gray-scale image
// return the new gray image (width is decreased by 1)

GrayImage remove_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    for (size_t row(0); row < seam.size(); ++row) {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}

// Remove specified seam from an RGB image
// return the new RGB image (width is decreased by 1)
RGBImage remove_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    for (size_t row(0); row < seam.size(); ++row) {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}
