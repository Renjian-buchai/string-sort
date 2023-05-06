#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

int main(int argc, char** argv) {
  // Flags:
  // 0: trim spaces
  std::array<bool, 1> flags;
  flags.fill(false);

  std::string input_string;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-T") {
      flags[0] = true;
    } else {
      (input_string += argv[i]) += " ";
    }
  }

  if (flags[0]) {
    input_string.erase(
        std::remove_if(input_string.begin(), input_string.end(), ::isspace),
        input_string.end());
  }

  std::sort(input_string.begin(), input_string.end());

  std::cout << input_string << std::endl;

  return 0;
}