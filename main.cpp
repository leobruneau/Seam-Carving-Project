//
//  main.cpp
//  SeamCarving
//
//  Created by Barbara Jobstmann on 15.06.21.
//
//

#include <cassert>
#include <iostream>
#include <tgmath.h>
#include <vector>

#include "helper.h"
#include "seam.h"
#include "unit_test.h"

void test_equality(std::string const& path1, std::string const& path2);
void test_to_gray(std::string const& in_path);
void test_smooth(std::string const& in_path);
void test_sobelX(std::string const& in_path);
void test_sobelY(std::string const& in_path);
void test_sobel(std::string const& in_path);
void test_sharpen(std::string const& in_path);
void test_smooth_to_sobel(std::string const& in_path);
void test_hightlight_seam(std::string const& in_path, int num);
void test_remove_seam(std::string const& in_path, int num);

int main(int argc, char **argv)
{
    // run_unit_tests();

    // Initialize with a default value
    std::string in_path = "img/americascup.jpg";
    std::string out_path = "test.png";
    std::string check_path1 = "expected_outputs/americascup_grayed.png";
    std::string check_path2 = "outputs/test_grayed.png";
    if (argc > 1 && argc <= 3) {
        // Change it if the user defined a image path
        in_path = argv[1];
    } else if (argc > 3) {
        std::cerr << "error: Too many arguments" << std::endl;
        std::cerr << "Usage:\n\t./prog [input_path] [output_path]" << std::endl;
        return -1;
    }

    // // Uncomment for testing different phases:
    // test_equality(check_path1, check_path2);
    test_to_gray(in_path);
    test_smooth(in_path);
    test_sobelX(in_path);
    test_sobelY(in_path);
    test_sobel(in_path);
    test_sharpen(in_path);
    test_smooth_to_sobel(in_path);
    // int num_seam(10); /* high value will slow things down */
    // test_hightlight_seam(in_path, num_seam);
    // test_remove_seam(in_path, num_seam);
    // Graph graph;
    // RGBImage image(read_image(in_path));
    // GrayImage img = to_gray(image);
    // graph = create_graph(img);
    // std::cout << img[0].size() << "x" << img.size() << std::endl;
    // std::cout << "successors for node 474000: " << graph[474000].successors.size() << std::endl;
    // std::cout << "graph size: " << graph.size() << std::endl;
    // std::cout << "successor 1: " << (graph[474000].successors)[0] << std::endl;
    // std::cout << "successor 2: " << (graph[474000].successors)[1] << std::endl;
    // std::cout << "successor 3: " << (graph[474000].successors)[2] << std::endl;

    return 0;
}

void test_equality(std::string const& path1, std::string const& path2) {
  if(image_equality_checker(path1, path2)) {
    std::cout << "The two images are identical! Pixel by pixel!" << std::endl;
  } else {
    std::cout << "Sorry, there seems to be some difference between the two." << std::endl;
  }
}

void test_to_gray(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        write_image(to_RGB(gray_image), "outputs/test_grayed.png");
    }
}

void test_smooth(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage smoothed_image(smooth(gray_image));
        write_image(to_RGB(smoothed_image), "outputs/test_smoothed.png");
    }
};

void test_sobelX(std::string const& in_path) {
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sobelXed(sobelX(gray_image));
        write_image(to_RGB(sobelXed), "outputs/test_sobelX.png");
    }
}

void test_sobelY(std::string const& in_path) {
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sobelYed(sobelY(gray_image));
        write_image(to_RGB(sobelYed), "outputs/test_sobelY.png");
    }
}

void test_sobel(std::string const& in_path)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sobeled_image(sobel(gray_image));
        write_image(to_RGB(sobeled_image), "outputs/test_sobel.png");
    }
}

void test_sharpen(std::string const& in_path) {
    RGBImage image(read_image(in_path));
    if(!image.empty()) {
        GrayImage gray_image(to_gray(image));
        GrayImage sharpened_image(sharpen(gray_image));
        write_image(to_RGB(sharpened_image), "outputs/test_sharpen.png");
    }
}

void test_smooth_to_sobel(std::string const& in_path) {
  RGBImage image(read_image(in_path));
  if(!image.empty()) {
    GrayImage gray_image(to_gray(image));
    GrayImage smooth_image(smooth(gray_image));
    GrayImage sobeled_image(sobel(smooth_image));
    write_image(to_RGB(sobeled_image), "outputs/test_smooth_sobel.png");
  }
}

void test_hightlight_seam(std::string const& in_path, int num)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        GrayImage gray_image(to_gray(image));
        for (int i = 0; i < num; ++i) {
            GrayImage sobeled_image(sobel(smooth(gray_image)));
            Path seam = find_seam(sobeled_image);
            gray_image = highlight_seam(gray_image, seam);
        }
        write_image(to_RGB(gray_image), "outputs/test_highlighted_seam.png");
    }
}

void test_remove_seam(std::string const& in_path, int num)
{
    RGBImage image(read_image(in_path));
    if (!image.empty()) {
        for (int i = 0; i < num; ++i) {
            GrayImage gray_image(to_gray(image));
            GrayImage sobeled_image(sobel(smooth(gray_image)));
            Path seam = find_seam(sobeled_image);
            image = remove_seam(image, seam);
        }
        write_image(image, "outputs/test_removed_seam.png");
    }
};
