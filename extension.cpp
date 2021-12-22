#include <iostream>
#include <vector>
#include <cmath>
#include "extension.h"
#include "seam_types.h"
#include "helper.h"
#include "seam.h"

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

// constexpr double INF(std::numeric_limits<double>::max());


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

// Gaussian blur kernel
GrayImage gaussian_blur(const GrayImage& gray)
{
    GrayImage gaussian_blurred;
    Kernel ker {{1.0,  4.0,  6.0,  4.0, 1.0},
                {4.0, 16.0, 24.0, 16.0, 4.0},
                {6.0, 24.0, 36.0, 24.0, 6.0},
                {4.0, 16.0, 24.0, 16.0, 4.0},
                {1.0,  4.0,  6.0,  4.0, 1.0}};

    for (auto& line: ker) {
        for (auto& element: line) {
            element = element/256;
        }
    }

    gaussian_blurred = filter(gray, ker);
    return gaussian_blurred;
}

// Smooth function implementing a slightly different kernel
GrayImage smooth2(const GrayImage &gray)
{
  GrayImage smoothed;
  Kernel ker { {0.0625, 0.125, 0.0625},
               {0.125,  0.25,  0.125 },
               {0.0625, 0.125, 0.0625} };
  smoothed = filter(gray, ker);
  return smoothed;
}

// Added function implementing a particular kernel that increases constrast on the image
GrayImage sharpen(const GrayImage& gray)
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

// Function to check if two images are equal, pixel by pixel
bool image_equality_checker(std::string const& path1, std::string const& path2) {
  RGBImage image1 = read_image(path1);
  RGBImage image2 = read_image(path2);
  if((image1.size() == image2.size()) && (image1[0].size() == image2[0].size())) {
    for(size_t i(0); i < image1.size(); ++i) {
      for(size_t j(0); j < image1[i].size(); ++j) {
        if(image1[i][j] != image2[i][j]) return false;
      }
    }
  } else {
    std::cout << "Checking failed: two different images. Cannot compare." << std::endl;
    return false;
  }
  return true;
}

// Function that takes in two images and compares each pixel to verify that the two are identical
void test_equality(std::string const& path1, std::string const& path2)
{
  if(image_equality_checker(path1, path2)) {
    std::cout << "The two images are identical! Pixel by pixel!" << std::endl;
  } else {
    std::cout << "Sorry, there seems to be some difference between the two." << std::endl;
  }
}

// Finding successors for one node in the graph
Successors find_successors(const GrayImage &gray, const size_t &id)
{
    Successors successors;
    successors.push_back(id+gray[0].size() - 1);
    successors.push_back(id+gray[0].size());
    successors.push_back(id+gray[0].size() + 1);
    return successors;
}

// Recursive function that finds the path from a starting to an ending node in a graph
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
    write_image(to_RGB(seamed_image), "highlighted_vertical_and_horizontal_seams.png");
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

    write_image(flip_RGB_image(flipped), "removed_vertical_and_horizontal_seams.png");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// void func(const std::string& in_path, const unsigned int& num)
// {
//     RGBImage image(read_image(in_path));
//     if (!image.empty()) {
//         GrayImage gray(to_gray(image));
//         GrayImage gray_highlighted(to_gray(image));
//         GrayImage sobeled(sobel(gray));
//         std::vector<SeamPixel> seam;
//         SeamPixel pixel;
//         for (unsigned int i(0); i < num; ++i) {
//             path_finder(true, sobeled, seam, pixel);
//             for (auto pixel: seam) {
//                 gray_highlighted[pixel.row][pixel.column] = 0;
//                 // image[pixel.row][pixel.column] = 0x000ff;
//                 sobeled[pixel.row].erase(sobeled[pixel.row].begin() + pixel.column);
//                 gray[pixel.row].erase(gray[pixel.row].begin() + pixel.column);
//             }
//             seam.clear();
//         }
//         // write_image(image, "outputs/rgb_resized_image.png");
//         write_image(to_RGB(gray), "outputs/optimized_resizing.png");
//         write_image(to_RGB(gray_highlighted), "outputs/gray_highlighted_optimized.png");
//     }
// }
//
// // Function to create a bi-dimensional graph instead of a vector of nodes
// MatrixGraph CreateGraph(const GrayImage& sobeled)
// {
//     MatrixGraph graph;
//     Vertex node;
//     node.distance = INF;
//     for (size_t row(0); row < sobeled.size(); ++row) {
//         graph.push_back(std::vector<Vertex> (0));
//         for (size_t column(0); column < sobeled[row].size(); ++column) {
//             node.cost = sobeled[row][column];
//             graph[row].push_back(node);
//         }
//     }
//     // Creating and adding the FINISHING node
//     graph.push_back(std::vector<Vertex> (0));
//     node.cost = 0;
//     graph[sobeled.size()].push_back(node);
//     return graph;
// }
//
// // Really awful implementation of Dijkstra's Algorithm. Attempt to make it faster
// void Dijkstra(MatrixGraph& graph)
// {
//     bool modified(true);
//     graph[0][0].distance = 0;
//     for (size_t k(0); k < graph[0].size(); ++k) {
//         graph[0][k].distance = graph[0][k].cost;
//         graph[0][k].predecessor.row = INF;
//         graph[0][k].predecessor.column = INF;
//     }
//     while (modified) {
//         modified = false;
//         for (size_t i(1); i < graph.size()-1; ++i) {
//             for (size_t j(0); j < graph[i].size(); ++j) {
//                 if (i != graph.size()-2) {
//                     if (j == 0) {
//                         if (graph[i+1][0].distance > graph[i][j].distance + graph[i+1][0].cost) {
//                             graph[i+1][0].distance = graph[i][j].distance + graph[i+1][0].cost;
//                             graph[i+1][0].predecessor.row = i;
//                             graph[i+1][0].predecessor.column = j;
//                             modified = true;
//                         }
//                         if (graph[i+1][1].distance > graph[i][j].distance + graph[i+1][1].cost) {
//                             graph[i+1][1].distance = graph[i][j].distance + graph[i+1][1].cost;
//                             graph[i+1][1].predecessor.row = i;
//                             graph[i+1][1].predecessor.column = j;
//                             modified = true;
//                         }
//                     } else if (j == graph[i].size()-1) {
//                         if (graph[i+1][j].distance > graph[i][j].distance + graph[i+1][j].cost) {
//                             graph[i+1][j].distance = graph[i][j].distance + graph[i+1][j].cost;
//                             graph[i+1][j].predecessor.row = i;
//                             graph[i+1][j].predecessor.column = j;
//                             modified = true;
//                         }
//                         if (graph[i+1][j-1].distance > graph[i][j].distance + graph[i+1][j-1].cost) {
//                             graph[i+1][j-1].distance = graph[i][j].distance + graph[i+1][j-1].cost;
//                             graph[i+1][j-1].predecessor.row = i;
//                             graph[i+1][j-1].predecessor.column = j;
//                             modified = true;
//                         }
//                     } else {
//                         if (graph[i+1][j-1].distance > graph[i][j].distance + graph[i+1][j-1].cost) {
//                             graph[i+1][j-1].distance = graph[i][j].distance + graph[i+1][j-1].cost;
//                             graph[i+1][j-1].predecessor.row = i;
//                             graph[i+1][j-1].predecessor.column = j;
//                             modified = true;
//                         }
//                         if (graph[i+1][j].distance > graph[i][j].distance + graph[i+1][j].cost) {
//                             graph[i+1][j].distance = graph[i][j].distance + graph[i+1][j].cost;
//                             graph[i+1][j].predecessor.row = i;
//                             graph[i+1][j].predecessor.column = j;
//                             modified = true;
//                         }
//                         if (graph[i+1][j+1].distance > graph[i][j].distance + graph[i+1][j+1].cost) {
//                             graph[i+1][j+1].distance = graph[i][j].distance + graph[i+1][j+1].cost;
//                             graph[i+1][j+1].predecessor.row = i;
//                             graph[i+1][j+1].predecessor.column = j;
//                             modified = true;
//                         }
//                     }
//                 } else {
//                     if (graph[graph.size()-1][0].distance > graph[i][j].distance) {
//                         graph[graph.size()-1][0].distance = graph[i][j].distance;
//                         graph[graph.size()-1][0].predecessor.row = i;
//                         graph[graph.size()-1][0].predecessor.column = j;
//                         modified = true;
//                     }
//                 }
//             }
//         }
//     }
//     graph[graph.size()-1][0].predecessor.row = graph.size()-2;
//     for (size_t i(0); i < graph[0].size(); ++i) {
//         if (graph[graph.size()-2][i].distance < graph[graph.size()-1][0].distance) {
//             graph[graph.size()-1][0].distance = graph[graph.size()-2][i].distance;
//             graph[graph.size()-1][0].predecessor.column = i;
//         }
//     }
// }
//
// // Function to retrieve the seam (shortest path) from the graph
// void func3(const MatrixGraph& graph, std::vector<SeamPixel>& seam, const size_t& row, const size_t& column) {
//     if (row != INF && column != INF) {
//         SeamPixel node;
//         node.row = row;
//         node.column = column;
//         seam.push_back(node);
//         std::cerr << "DEBUGGING #1" << std::endl;
//         std::cerr << "Row: " << row << std::endl;
//         std::cerr << "Column: " << column << std::endl;
//         func3(graph, seam, graph[row][column].predecessor.row, graph[row][column].predecessor.column);
//     }
// }
//
// // Main function that from a given path creates the image and the relative graph and then finds n seams and removes them
// void func2(const std::string& in_path, const unsigned int& num) {
//     RGBImage image(read_image(in_path));
//     if (!image.empty()) {
//         GrayImage gray(to_gray(image));
//         GrayImage sobeled(sobel(gray));
//         std::vector<SeamPixel> seam;
//         MatrixGraph graph(CreateGraph(sobeled));
//         for (unsigned int i(0); i < num; ++i) {
//             Dijkstra(graph);
//             func3(graph, seam, graph[graph.size()-1][0].predecessor.row, graph[graph.size()-1][0].predecessor.column);
//             for (auto pixel: seam) {
//                 image[pixel.row][pixel.column] = 0x000ff;
//                 gray[pixel.row][pixel.column] = 0;
//                 graph[pixel.row].erase(graph[pixel.row].begin()+pixel.column);
//             }
//             seam.clear();
//         }
//         write_image(image, "outputs/rgb3seam.png");
//         write_image(to_RGB(gray), "outputs/gray3seam.png");
//     }
// }




































// end
