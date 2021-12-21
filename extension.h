#pragma once
#include "seam_types.h"
#include <vector>

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

// ADDED TYPES:
typedef size_t ID;
typedef std::vector<ID> Successors;
// struct SeamPixel {
//     size_t row;
//     size_t column;
// };
// struct Vertex
// {
//     double cost;
//     double distance;
//     SeamPixel predecessor;
// };
// typedef std::vector<std::vector<Vertex>> MatrixGraph;


// ADDED FUNCTIONS:
// int digit_counter(const int& num);
// int binary_to_decimal(const int& bin);
int decimal_to_binary(const int& dec);
bool image_equality_checker(std::string const& path1, std::string const& path2);
void test_equality(std::string const& path1, std::string const& path2);
GrayImage smooth2(const GrayImage &gray);
GrayImage sharpen(const GrayImage& gray);
GrayImage gaussian_blur(const GrayImage& gray);
void test_sharpen(std::string const& in_path);
void test_smooth_to_sobel(std::string const& in_path);
void test_sobelX(std::string const& in_path);
void test_sobelY(std::string const& in_path);
Successors find_successors(const GrayImage &gray, const size_t &id);
void find_path(const Graph& graph, const ID& from, const ID& to, Path& path);

// *****************
// |  GO FURTHER!  |
// *****************

GrayImage flip_gray_image(const GrayImage& gray);
RGBImage flip_RGB_image(const RGBImage& image);
void test_to_gray_flipped(std::string const& in_path);
void find_all_seams(const std::string& in_path, const int& num);
void resize_image(const std::string& in_path, const int& num);

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// void func(const std::string& in_path, const unsigned int& num);
// MatrixGraph CreateGraph(const GrayImage& sobeled);
// void Dijkstra(MatrixGraph& graph);
// void func3(const MatrixGraph& graph, std::vector<SeamPixel>& seam, const size_t& row, const size_t& column);
// void func2(const std::string& in_path, const unsigned int& num);














// end
