#pragma once
#include "seam_types.h"

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */

// ADDED FUNCTIONS:
// int digit_counter(const int& num);
// int binary_to_decimal(const int& bin);
int decimal_to_binary(const int& dec);
void test_equality(std::string const& path1, std::string const& path2);
void test_sharpen(std::string const& in_path);
void test_smooth_to_sobel(std::string const& in_path);
Successors find_successors(const GrayImage &gray, const size_t &id);
void find_path(const Graph& graph, const ID& from, const ID& to, Path& path);
