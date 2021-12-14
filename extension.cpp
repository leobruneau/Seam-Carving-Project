#include <iostream>
#include <vector>
#include <cmath>
#include "extension.h"
#include "seam_types.h"
#include "helper.h"
#include "seam.h"

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

// int digit_counter(const int& num) {
//   // Function to count the number of digits in an integer that will be used
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
//
// // Function to convert from binary to decimal - which now we see is actually useless
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
//
// // Function to convert from decimal to binary - which now we see is actually useless
// int decimal_to_binary(const int& dec) {
//   int i(0), n(0);
//   int bin = dec;
//   bool flag(true);
//     while(flag) {
//         if(pow(2,i) >= n) {
//         flag = false;
//         } else {
//         ++i;
//         }
//     }
//     for(int j(i); j > 0; --j) {
//         if(pow(2, j) <= n) {
//         bin = bin*10 + 1;
//         n -= pow(2, j);
//         } else {
//         bin *= 10;
//         }
//     }
//     return bin;
// }

// Function that implements a different kernel that increases image contrast
void test_sharpen(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if(!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sharpened_image(sharpen(gray_image));
        write_image(to_RGB(sharpened_image), "test_sharpen.png");
    }
}

// Function that creates sobeled image by first apllying smooth filter to see the difference
void test_smooth_to_sobel(std::string const& in_path)
{
  RGBImage image(read_image(in_path));
  if(!image.empty()) {
    GrayImage gray_image(to_gray(image));
    GrayImage smooth_image(smooth(gray_image));
    GrayImage sobeled_image(sobel(smooth_image));
    write_image(to_RGB(sobeled_image), "test_smooth_sobel.png");
  }
}

// Function to test only the sobelX kernel and produce an image after applying just this filter to the gray image
void test_sobelX(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sobelXed(sobelX(gray_image));
        write_image(to_RGB(sobelXed), "test_sobelX.png");
    }
}

// Function to test only the sobelY kernel and produce an image after applying just this filter to the gray image
void test_sobelY(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sobelYed(sobelY(gray_image));
        write_image(to_RGB(sobelYed), "test_sobelY.png");
    }
}

// functions that takes in two images and compares each pixel to verify that the two are identical
void test_equality(std::string const& path1, std::string const& path2)
{
  if(image_equality_checker(path1, path2)) {
    std::cout << "The two images are identical! Pixel by pixel!" << std::endl;
  } else {
    std::cout << "Sorry, there seems to be some difference between the two." << std::endl;
  }
}

// Finding successors for each node in the graph
Successors find_successors(const GrayImage &gray, const size_t &id)
{
    Successors successors;
    successors.push_back(id+gray[0].size() - 1);
    successors.push_back(id+gray[0].size());
    successors.push_back(id+gray[0].size() + 1);
    return successors;
}

// Recursive functions that composes the graph from a stanrting and an ending node in a graph
void find_path(const Graph& graph, const ID& from, const ID& to, Path& path)
{
  if(from != graph[to].predecessor_to_target) {
    path.insert(path.begin(), graph[to].predecessor_to_target);
    find_path(graph, from, graph[to].predecessor_to_target, path);
  }
}

// *****************
// |  GO FURTHER!  |
// *****************

// Function that takes as input a gray image and rotates it
// in order to then create the relative graph and find path and find horizontal seams
GrayImage flip_gray_image(const GrayImage& gray)
{
  GrayImage flipped;
  for(size_t column(0); column < gray[0].size(); ++column) {

    flipped.push_back(std::vector<double> (0));
    for(size_t row(0); row < gray.size(); ++row) {

      flipped[column].push_back(gray[row][column]);
    }
  }
  return flipped;
}

// Function that takes as input an RGB image and rotates it by 90 degrees
RGBImage flip_RGB_image(const RGBImage& image)
{
  RGBImage flipped;
  for(size_t column(0); column < image[0].size(); ++column) {

    flipped.push_back(std::vector<int> (0));
    for(size_t row(0); row < image.size(); ++row) {

      flipped[column].push_back(image[row][column]);
    }
  }
  return flipped;
}

// Just calling create graph with flipped ("rotated") image
Graph create_graph_flipped(const GrayImage &gray)
{
    return create_graph(flip_gray_image(gray));
}

void find_best_predecessors(Graph &graph)
{
  Path path;
  bool modified(true);
  graph[from].distance_to_target = graph[from].costs;
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
}

void resize_image(const std::string& path, const size_t& resizing_factor)
{
    RGBImage image(read_image(path));
    RGBImage rotated_image(flip_RGB_image(image));

    Paths paths, rotated_paths;
    Seams seams, rotated_seams;


    if (!image.empty()) {
        GrayImage gray(to_gray(image));
        GrayImage rotated_gray(to_gray(rotated_image));
        Graph graph(create_graph(gray));
        Graph rotated_graph(create_graph(rotated_gray));
        find_best_predecessors(graph);
        find_best_predecessors(rotated_graph);
        for (size_t i(0); i < resizing_factor; ++i) {
            paths.push_back(std::vector<ID> (0));
            find_path(graph, (graph.size() - 2), (graph.size() - 1), paths[i]);
            // to continue...
        }
    }
}






































// end
