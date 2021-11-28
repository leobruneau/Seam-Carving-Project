#include <iostream>
#include <cmath>
#include <array>
#include <string>
#include <vector>


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

  int i(0), n(0), dec(0);
  bool flag(true);
  for(int k(0); k < 17; ++k) {
    flag = true; n = k; i = 0; dec = 0;
    while(flag) {
      if(pow(2,i) >= n) {
        flag = false;
      } else {
        ++i;
      }
    }

    for(int j(i); j >= 0; --j) {
      if(pow(2, j) <= n) {
        dec = dec*10 + 1;
        n -= pow(2, j);
      } else {
        dec *= 10;
      }
    }
    std::cout << dec << std::endl;
  }

  return 0;
}












// end
