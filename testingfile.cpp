#include <iostream>
#include <cmath>
#include <array>
#include <string>
#include <vector>

int decimal_to_binary(const int& dec);

int main() {
  // int a(0);
  // std::cout << "Enter an integer: ";
  // std::cin >> a;
  // bool flag(true); int i(1); int size(0);
  // while(flag) {
  //   if(a/pow(10, i) < 1) {
  //     size = i;
  //     flag = false;
  //   } else {
  //     ++i;
  //   }
  // }
  // std::cout << a << " has " << size << " digits" << std::endl;

  // int i(0), n(0), dec(0);
  // bool flag(true);
  // for(int k(0); k < 17; ++k) {
  //   flag = true; n = k; i = 0; dec = 0;
  //   while(flag) {
  //     if(pow(2,i) >= n) {
  //       flag = false;
  //     } else {
  //       ++i;
  //     }
  //   }

  //   for(int j(i); j >= 0; --j) {
  //     if(pow(2, j) <= n) {
  //       dec = dec*10 + 1;
  //       n -= pow(2, j);
  //     } else {
  //       dec *= 10;
  //     }
  //   }
  //   std::cout << dec << std::endl;
  // }


  int a(0b000111001100110001011110), b(0b00011100), c(0b11001100), d(0b01011110);
  std::cout << a << std::endl;
  std::cout << b << ", " << c << ", " << d << std::endl;
  std::cout << d + c*256 + b*256*256 << std::endl;
  std::cout << decimal_to_binary(d + c*256 + b*256*256) << std::endl;

  return 0;
}


int decimal_to_binary(const int& dec) {
  int i(0), n(0);
  long long int bin = dec;
  bool flag(true);
    while(flag) {
        if(pow(2,i) >= n) {
        flag = false;
        } else {
        ++i;
        }
    }
    for(int j(i); j >= 0; --j) {
        if(pow(2, j) <= n) {
        bin = bin*10 + 1;
        n -= pow(2, j);
        } else {
        bin *= 10;
        }
    }
    return bin;
}











// end
