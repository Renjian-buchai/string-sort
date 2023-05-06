#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  // Flags:
  // 0: trim spaces
  // 1: converts to upper
  bool flags[3] = {0};
  std::string input_string;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-T") {
      flags[0] = true;
      continue;
    }

    if (std::string(argv[i]) == "-U") {
      flags[1] = true;
      continue;
    }

    if (std::string(argv[i]) == "-L") {
      flags[2] = true;
      continue;
    }

    (input_string += argv[i]) += " ";
  }

  if (flags[1] + flags[2] == 2) {
    std::cout
        << "Invalid argument. Cannot have both -U and -L flags at same time";
    return 1;
  }

  if (flags[0]) {
    input_string.erase(
        std::remove_if(input_string.begin(), input_string.end(), ::isspace),
        input_string.end());
  }

  if (flags[1]) {
    for (auto it = input_string.begin(); it != input_string.end(); ++it)
      *it = 96 < *it && *it < 122 ? *it -= 32 : *it;
  }

  if (flags[2]) {
    for (auto it = input_string.begin(); it != input_string.end(); ++it)
      *it = 65 < *it && *it < 93 ? *it += 32 : *it;
  }

  std::sort(input_string.begin(), input_string.end());

  std::cout << input_string << std::endl;

  return 0;
}