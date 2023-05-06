#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string total = "";

  for (int i = 1; i < argc; ++i) {
    total += std::string(argv[i]) + " ";
  }
  std::remove(total.begin(), total.end(), ' ');
  std::sort(total.begin(), total.end());

  std::cout << total;

  return 0;
}