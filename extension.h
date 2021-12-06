#pragma once
#include "seam_types.h"
// ADDED FUNCTIONS:
// int digit_counter(const int& num);
// int binary_to_decimal(const int& bin);
int decimal_to_binary(const int& dec);

Successors find_successors(const GrayImage &gray, const size_t &id);
void find_path(const Graph& graph, const ID& from, const ID& to, Path& path);

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
