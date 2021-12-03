#pragma once

#include <string>
#include <vector>

typedef std::vector<std::vector<int>> RGBImage;
typedef std::vector<std::vector<double>> GrayImage;
typedef std::vector<std::vector<double>> Kernel;
typedef size_t ID;
typedef std::vector<ID> Path;
typedef std::vector<ID> Successors;

struct Node {
    std::vector<ID> successors;
    double costs;
    double distance_to_target;
    size_t predecessor_to_target;
};

typedef std::vector<Node> Graph;
