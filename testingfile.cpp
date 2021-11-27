#include <iostream>
#include <cmath>
#include <array>
#include <string>
#include <vector>


int main() {
  int a(0);
  std::cout << "Enter an integer: ";
  std::cin >> a;
  bool flag(true); int i(1); int size(0);
  while(flag) {
    if(a/pow(10, i) < 1) {
      size = i;
      flag = false;
    } else {
      ++i;
    }
  }
  std::cout << a << " has " << size << " digits" << std::endl;

  return 0;
}
