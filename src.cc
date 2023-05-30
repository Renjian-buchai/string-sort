#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  // Flags:
  // 0: trim spaces
  // 1: converts to upper
  uint8_t flags = 0;
  std::string input_string;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-T") {
      flags |= 0b1000'0000;
      continue;
    }

    if (std::string(argv[i]) == "-U") {
      flags |= 0b0100'0000;
      continue;
    }

    if (std::string(argv[i]) == "-L") {
      flags |= 0b0010'0000;
      continue;
    }

    if (std::string(argv[i]) == "-H") {
      flags |= 0b0001'0000;
      continue;
    }

    (input_string += argv[i]) += " ";
  }

  if (flags & 0b0001'0000) {
    std::cout << "StrSort Documentation\n"
                 "Sample usage:\n"
                 "> strSort This will be sorted!\n"
                 "Output:\n"
                 "'    !bdeehiillorssttw'\n"
                 "\n"
                 "Flags:\n"
                 "'-T': Trims spaces from the space\n"
                 "'-U': Converts all characters to uppercase\n"
                 "      Cannot be used in conjuction with flag '-L'\n"
                 "'-L': Converts all characters to lowercase\n"
                 "      Cannot be used in conjuction with flag '-U'\n"
                 "'-H': Help\n";
    return 0;
  }

  if (!(flags & 0b0110'0000)) {
    std::cout
        << "Invalid argument. Cannot have both -U and -L flags at same time";
    return 1;
  }

  if (flags & 0b1000'0000) {
    input_string.erase(
        std::remove_if(input_string.begin(), input_string.end(), ::isspace),
        input_string.end());
  }

  if (flags & 0b0100'0000) {
    for (auto it = input_string.begin(); it != input_string.end(); ++it)
      *it = 96 < *it && *it <= 122 ? *it -= 32 : *it;
  }

  if (flags & 0b0010'0000) {
    for (auto it = input_string.begin(); it != input_string.end(); ++it)
      *it = 65 <= *it && *it < 93 ? *it += 32 : *it;
  }

  std::sort(input_string.begin(), input_string.end());

  std::cout << input_string << std::endl;

  return 0;
}