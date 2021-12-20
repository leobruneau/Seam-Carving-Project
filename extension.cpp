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

// Added function implementing a particular kernel that increases constrast on the image
GrayImage sharpen(const GrayImage &gray)
{
    GrayImage sharpened;
    Kernel ker { { 0,-1,  0},
                 {-1, 5, -1},
                 { 0,-1,  0} };
    sharpened = filter(gray, ker);
    return sharpened;
}

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

// Find and highlight vertical and horizontal seams
void find_all_seams(const std::string& in_path, const int& num)
{
    RGBImage image(read_image(in_path));
    RGBImage flipped(flip_RGB_image(image));

    GrayImage vertical_gray(to_gray(image));
    if (!image.empty()) {
        for (int i(0); i < num; ++i) {
            GrayImage vertical_sobeled(sobel(smooth(vertical_gray)));
            Path vertical_seam = find_seam(vertical_sobeled);
            vertical_gray = highlight_seam(vertical_gray, vertical_seam);
        }
    }

    GrayImage horizontal_gray(to_gray(flipped));
    if (!flipped.empty()) {
        for(int i(0); i < num; ++i) {
            GrayImage horizontal_sobeled(sobel(smooth(horizontal_gray)));
            Path horizontal_seam = find_seam(horizontal_sobeled);
            horizontal_gray = highlight_seam(horizontal_gray, horizontal_seam);
        }
    }

    horizontal_gray = flip_gray_image(horizontal_gray);
    GrayImage seamed_image(to_gray(image));
    if(vertical_gray.size() == horizontal_gray.size() && vertical_gray[0].size() == horizontal_gray[0].size()) {
        for(size_t i(0); i < vertical_gray.size(); ++i) {
            for(size_t j(0); j < vertical_gray[i].size(); ++j) {
                if(vertical_gray[i][j] == 0 ||  horizontal_gray[i][j] == 0) {
                    seamed_image[i][j] = 0;
                }
            }
        }
    }
    write_image(to_RGB(seamed_image), "outputs/highlighted_seams.png");
}

// Find and remove horizontal and vertical seams
void resize_image(const std::string& in_path, const int& num)
{
    RGBImage image(read_image(in_path));

    GrayImage step1(to_gray(image));
    if (!image.empty()) {
        for (int i(0); i < num; ++i) {
            GrayImage vertical_gray(to_gray(image));
            GrayImage vertical_sobeled(sobel(smooth(vertical_gray)));
            Path vertical_seam = find_seam(vertical_sobeled);
            image = remove_seam(image, vertical_seam);
        }
    }

    RGBImage flipped(flip_RGB_image(image));
    if (!image.empty()) {
        for(int i(0); i < num; ++i) {
            GrayImage horizontal_gray(to_gray(flipped));
            GrayImage horizontal_sobeled(sobel(smooth(horizontal_gray)));
            Path horizontal_seam = find_seam(horizontal_sobeled);
            flipped = remove_seam(flipped, horizontal_seam);
        }
    }

    write_image(flip_RGB_image(flipped), "outputs/removed_seams.png");
}







































// end
