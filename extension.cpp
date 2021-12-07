#include "extension.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "seam_types.h"
#include "helper.h"
#include "seam.h"

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

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
void test_sharpen(std::string const& in_path) {
    RGBImage image(read_image(in_path));
    if(!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sharpened_image(sharpen(gray_image));
        write_image(to_RGB(sharpened_image), "outputs/test_sharpen.png");
    }
}

// Function that creates sobeled image by first apllying smooth filter to see the difference
void test_smooth_to_sobel(std::string const& in_path) {
  RGBImage image(read_image(in_path));
  if(!image.empty()) {
    GrayImage gray_image(to_gray(image));
    GrayImage smooth_image(smooth(gray_image));
    GrayImage sobeled_image(sobel(smooth_image));
    write_image(to_RGB(sobeled_image), "outputs/test_smooth_sobel.png");
  }
}

// functions that takes in two images and compares each pixel to verify that the two are identical
void test_equality(std::string const& path1, std::string const& path2) {
  if(image_equality_checker(path1, path2)) {
    std::cout << "The two images are identical! Pixel by pixel!" << std::endl;
  } else {
    std::cout << "Sorry, there seems to be some difference between the two." << std::endl;
  }
}

// finding successors for each node in the graph
Successors find_successors(const GrayImage &gray, const size_t &id) {
    Successors successors;
    successors.push_back(id+gray[0].size() - 1);
    successors.push_back(id+gray[0].size());
    successors.push_back(id+gray[0].size() + 1);
    return successors;
}

// Recursive functions that composes the graph from a stanrting and an ending node in a graph
void find_path(const Graph& graph, const ID& from, const ID& to, Path& path) {
  if(from != graph[to].predecessor_to_target) {
    path.insert(path.begin(), graph[to].predecessor_to_target);
    find_path(graph, from, graph[to].predecessor_to_target, path);
  }
}
