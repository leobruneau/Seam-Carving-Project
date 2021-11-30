#include "extension.h"
#include <iostream>
#include <vector>
#include <cmath>

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

int decimal_to_binary(const int& dec) {
  int i(0), n(0);
  int bin = dec;
  bool flag(true);
    while(flag) {
        if(pow(2,i) >= n) {
        flag = false;
        } else {
        ++i;
        }
    }
    for(int j(i); j > 0; --j) {
        if(pow(2, j) <= n) {
        bin = bin*10 + 1;
        n -= pow(2, j);
        } else {
        bin *= 10;
        }
    }
    return bin;
}

Successors find_successors(const GrayImage &gray, const size_t &id) {
    Successors successors;
    successors.push_back(id+gray[0].size() - 1);
    successors.push_back(successors[0] + 1);
    successors.push_back(successors[1] + 1);
    return successors;
}

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
