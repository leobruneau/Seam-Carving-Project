#include <iostream>
#include <cassert>
#include <limits>
#include <tgmath.h>
#include <cmath>
#include <vector>
#include "seam.h"
#include "extension.h"

constexpr double INF(std::numeric_limits<double>::max());

// ***********************************
// TASK 1: COLOR
// ***********************************

// Returns red component (in the scale 0.0-1.0) from given RGB color.
double get_red(int rgb) {
    double red_component(.0);
    int r = rgb >> 16;
    r = r & 0b11111111;
    red_component = r/255.0;
    return red_component;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb) {
    double green_component(.0);
    int g = rgb >> 8;
    g = g & 0b11111111;
    green_component = g/255.0;
    return green_component;
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb) {
   double blue_component(.0);
    int b(rgb);
    b = b & 0b11111111;
    blue_component = b/255.0;
    return blue_component;
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb) {
    double grey_component(.0);
    grey_component = (get_red(rgb) + get_green(rgb) + get_blue(rgb))/3;
    return grey_component;
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue) {
    int r(red*255), g(green*255), b(blue*255);
    int rgb(0b00000000);
    // rgb = (rgb << 8) + decimal_to_binary(r);
    rgb = (rgb << 8) + r;
    // rgb = (rgb << 8) + decimal_to_binary(g);
    rgb = (rgb << 8) + g;
    // rgb = (rgb << 8) + decimal_to_binary(b);
    rgb = (rgb << 8) + b;
    return rgb;
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray) {
    int rgb;
    rgb = get_RGB(gray, gray, gray);
    return rgb;
}

// Converts  RGB image to grayscale double image.
GrayImage to_gray(const RGBImage &cimage) {
    GrayImage gimage;
    for(size_t i(0); i < cimage.size(); ++i) {
      gimage.push_back(std::vector<double> (0));
      for(size_t j(0); j < cimage[i].size(); ++j) {
        gimage[i].push_back(get_gray(cimage[i][j]));
      }
    }
    return gimage;
}

// Converts grayscale double image to an RGB image.
RGBImage to_RGB(const GrayImage &gimage) {
    RGBImage cimage;
    for(size_t i(0); i < gimage.size(); ++i) {
      cimage.push_back(std::vector<int> (0));
      for(size_t j(0); j < gimage[i].size(); ++j) {
        cimage[i].push_back(get_RGB(gimage[i][j]));
      }
    }
    return cimage;
}

// ***********************************
// TASK 2: FILTER
// ***********************************

// Get a pixel without accessing out of bounds
// return nearest valid pixel color
void clamp(long &val, long max) {
  if(val < 0) val = 0;
  if(val >= max) val = max;
}

// Convolve a single-channel image with the given kernel.
GrayImage filter(const GrayImage &gray, const Kernel &kernel) {
    double average_pixel(.0);
    long val_k(0), val_l(0);
    GrayImage filtered;
    for(size_t i(0); i < gray.size(); ++i) {
        filtered.push_back(std::vector<double> (0));
        for(size_t j(0); j < gray[i].size(); ++j) {
            for(size_t k(0); k < kernel.size(); ++k) {
                for(size_t l(0); l < kernel[k].size(); ++l) {
                    val_k = i - 1 + k; clamp(val_k, gray.size()-1);
                    val_l = j - 1 + l; clamp(val_l, gray[i].size()-1);
                    average_pixel += kernel[k][l]*gray[val_k][val_l];
                }
            }
            filtered[i].push_back(average_pixel);
            average_pixel = 0; // we forgot to inizialize it back to zero at each new pixel !
        }
    }
    return filtered;
}

// Smooth a single-channel image
GrayImage smooth(const GrayImage &gray) {
    GrayImage smoothed;
    Kernel ker { {0.1,0.1,0.1},
                 {0.1,0.2,0.1},
                 {0.1,0.1,0.1} };
    smoothed = filter(gray, ker);
    return smoothed;
}

GrayImage smooth2(const GrayImage &gray) {
  GrayImage smoothed;
  Kernel ker { {0.0625, 0.125, 0.0625},
               {0.125,  0.25,  0.125 },
               {0.0625, 0.125, 0.0625}};
  smoothed = filter(gray, ker);
  return smoothed;
}

// Compute horizontal Sobel filter
GrayImage sobelX(const GrayImage &gray) {
    GrayImage sobelXed;
    Kernel ker { {-1, 0, 1},
                 {-2, 0, 2},
                 {-1, 0, 1} };
    sobelXed = filter(gray, ker);
    return sobelXed;
}

// Compute vertical Sobel filter
GrayImage sobelY(const GrayImage &gray) {
    GrayImage sobelYed;
    Kernel ker { {-1, -2, -1},
                 { 0,  0,  0},
                 { 1,  2,  1} };
    sobelYed = filter(gray, ker);
    return sobelYed;
}

// Compute the magnitude of combined Sobel filters
GrayImage sobel(const GrayImage &gray) {
    GrayImage sobeled, sobelXed, sobelYed;
    double sobel_pixel(.0);
    Kernel kerY { {-1, -2, -1},
                  { 0,  0,  0},
                  { 1,  2,  1} };
    Kernel kerX { {-1, 0, 1},
                  {-2, 0, 2},
                  {-1, 0, 1} };
    sobelXed = filter(gray, kerX);
    sobelYed = filter(gray, kerY);
    for(size_t i(0); i < gray.size(); ++i) {
      sobeled.push_back(std::vector<double> (0));
      for(size_t j(0); j < gray[i].size(); ++j) {
        sobel_pixel = sqrt(pow(sobelXed[i][j], 2) + pow(sobelYed[i][j], 2));
        sobeled[i].push_back(sobel_pixel);
        sobel_pixel = 0;
      }
    }
    return sobeled;
}

GrayImage sharpen(const GrayImage &gray) {
    GrayImage sharpened;
    Kernel ker { { 0,-1,  0},
                 {-1, 5, -1},
                 { 0,-1,  0} };
    sharpened = filter(gray, ker);
    return sharpened;
}

// ************************************
// TASK 3: SEAM
// ************************************

Graph create_graph(const GrayImage &gray) {
    Graph graph;
    Node node;
    // GrayImage sobeled;          the cost are the value of the pixel in the gray image
    // sobeled = sobel(gray);
    ID id;
    Successors successors;
    for(size_t i(0); i < gray.size(); ++i) {
        for(size_t j(0); j < gray[i].size(); ++j) {
          id = i*(gray[i].size()) + j;
          if(i == gray.size() - 1) {
            node.successors.push_back(gray.size()*gray[0].size() + 1);
          } else {
            successors = find_successors(gray, id);
            for(size_t k(0); k < 3; ++k) {
              if((successors[k] >= (i+1)*gray[0].size()) and (successors[k] <= (i+2)*gray[0].size() - 1)) {
                (node.successors).push_back(successors[k]);
              }
            }
          }
          // node.costs = sobeled[i][j];
          node.costs = gray[i][j];
          node.distance_to_target = INF;
          node.predecessor_to_target = 0;
          graph.push_back(node);
          (node.successors).clear();
          node.costs = 0;
        }
    }
    // initilizing and adding starting node
    for(size_t i(0); i < gray[0].size(); ++i) {
      node.successors.push_back(i);
    }
    node.costs = 0;
    node.distance_to_target = INF;
    node.predecessor_to_target = 0;
    graph.push_back(node);
    node.successors.clear();

    //initializing and adding finishing node
    graph.push_back(node);

    return graph;
}

// Return shortest path from Node from to Node to
// The path does NOT include the from and to Node
Path shortest_path(Graph &graph, ID from, ID to) {
  Path path;
  bool modified(true);
  graph[from].distance_to_target = graph[from].costs;
  modified = true;
  while(modified) {
    modified = false;
    for(size_t i(0); i < graph.size(); ++i) {
      for(size_t j(0); j < (graph[i].successors).size(); ++j) {
        if(graph[graph[i].successors[j]].distance_to_target > graph[i].distance_to_target + graph[graph[i].successors[j]].costs) {
          graph[graph[i].successors[j]].distance_to_target = graph[i].distance_to_target + graph[graph[i].successors[j]].costs;
          graph[graph[i].successors[j]].predecessor_to_target = i;
          modified = true;
        }
      }
    }
  }
  // for(size_t i(0); i < graph.size(); ++i) {
  //   std::cout << "Predecessor for node " << i << ": " << graph[i].predecessor_to_target << std::flush << std::endl;
  // }

  find_path(graph, from, to, path);

  // Path shortest_path du premier successeur;
  // Path shortest_path du deuxieme successeur;
  // Path shortest_path du troisieme successeur;
  //
  // comparer les 3 costs et prendre le plus petit

  return path; // TODO MODIFY AND COMPLETE
}

Path find_seam(const GrayImage &gray) {
  // for loop shortest_path de la derniere ligne
  // prendre le plus petit cost
  // (copier) et enlever le path

  unsigned int width(gray[0].size()), height(gray.size());
  Graph graph(create_graph(gray));
  ID from(graph.size()-2), to(graph.size()-1);
  Path path(shortest_path(graph, from, to));
  Path seam;
  for(size_t i(0); i < path.size(); ++i) {
    for(size_t j(0); j < height; ++j) {
      if((path[i] >= j*width && (path[i] <= ((j+1)*width - 1))))
        seam.push_back(path[i] - j*width);
    }
  }

  return seam; // TODO MODIFY AND COMPLETE
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

// Remove specified seam from  a gray-scale image
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
