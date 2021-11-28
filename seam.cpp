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

// int digit_counter(const int& num) {
//   // function to count the number of digits in an integer that will be used
//   // in the function to convert from binary to decimal
//   bool flag(true);
//   int digits(0), i(1);
//   while(flag) {
//     if(num/pow(10, i) < 1) {
//       digits = i;
//       flag = false;
//     } else {
//       ++i;
//     }
//   }
//   return digits;
// }
// Added function to convert from binary to decimal - which now I see is actually useless
// int binary_to_decimal(const int& bin) {
//   int temp(0), decimal(0);
//   int digits = digit_counter(bin);
//   for(int i(0); i < digits; ++i) {
//     temp = bin >> i;
//     if((temp & 0b1) == 1) {
//       decimal += pow(2, i);
//     }
//   }
//   return decimal;
// }

int decimal_to_binary(const int& dec) {
  int i(0), n(0);
  int bin = dec;
  bool flag(true);
    while(flag) {
        if(pow(2,i) >= n) {
        flag = false;
        } else {
        ++i;
        }
    }
    for(int j(i); j > 0; --j) {
        if(pow(2, j) <= n) {
        bin = bin*10 + 1;
        n -= pow(2, j);
        } else {
        bin *= 10;
        }
    }
    return bin;
}

// Returns red component (in the scale 0.0-1.0) from given RGB color.
double get_red(int rgb)
{
    double red_component(.0);
    int r = rgb >> 16;
    r = r & 0b11111111;
    red_component = r/255.0;
    return red_component;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb)
{
    double green_component(.0);
    int g = rgb >> 8;
    g = g & 0b11111111;
    green_component = g/255.0;
    return green_component;
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb)
{
   double blue_component(.0);
    int b(rgb);
    b = b & 0b11111111;
    blue_component = b/255.0;
    return blue_component;
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb)
{
    double grey_component(.0);
    grey_component = (get_red(rgb) + get_green(rgb) + get_blue(rgb))/3;
    return grey_component;
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue)
{

    int r(red*255), g(green*255), b(blue*255);
    int rgb(0b00000000);
    rgb = (rgb << 8) + decimal_to_binary(r);
    std::cout << rgb << std::endl;
    rgb = (rgb << 8) + decimal_to_binary(g);
    std::cout << rgb << std::endl;
    rgb = (rgb << 8) + decimal_to_binary(b);
    std::cout << rgb << std::endl;
    return rgb; // TODO MODIFY AND COMPLETE
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray)
{
    int rgb;
    rgb = get_RGB(gray, gray, gray);
    return rgb; // TODO MODIFY AND COMPLETE
}

// Converts  RGB image to grayscale double image.
GrayImage to_gray(const RGBImage &cimage)
{
    GrayImage gimage;
    for(size_t i(0); i < cimage.size(); ++i) {
        gimage.push_back(std::vector<double> (0));
        for(size_t j(0); j < (cimage[i]).size(); ++j) {
            gimage[i].push_back(get_gray(cimage[i][j]));
        }
    }
    return gimage; // TODO MODIFY AND COMPLETE
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
