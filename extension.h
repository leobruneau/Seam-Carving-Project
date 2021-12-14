#pragma once
#include "seam_types.h"
#include <vector>

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

// ADDED TYPES:
typedef size_t ID;
typedef std::vector<ID> Successors;
typedef std::vector<Path> Paths;
typedef std::vector<std::vector<ID>> Seams;


// ADDED FUNCTIONS:
// int digit_counter(const int& num);
// int binary_to_decimal(const int& bin);
int decimal_to_binary(const int& dec);
void test_equality(std::string const& path1, std::string const& path2);
GrayImage sharpen(const GrayImage &gray);
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
Graph create_graph_flipped(const GrayImage &gray);
void resize_image(const std::string& path, const size_t& resizing_factor);
void find_best_predecessors(Graph &graph);
