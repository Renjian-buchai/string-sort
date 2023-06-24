#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "func.hh"

int main(int argc, char **argv) {
  /**
   * @brief Flags
   * @note 0: trim spaces
   * @note 1: convert characters to uppercase
   * @note 2: convert characters to lowercase
   * @note 3: Help
   * @note 4: Input from a file
   * @note 5: Output to a file
   * @note 6: Simple output to a file
   */
  uint8_t flags = 0;
  std::string inputString, oFilePath, filePath = "\n";
  (void)(lexicalAnalyser(argc, argv, filePath, flags, inputString, oFilePath));

  if (flags & (1 << 3)) {
    (void)(helpManual());
    (void)(std::exit(0));
  }

  if (flags & (1 << 1) && flags & (1 << 2)) {
    (void)(std::cerr << "Invalid argument. "
                        "Cannot have both -U and -L flags at same time");
    (void)(std::exit(1));
  }

  if (flags & (1 << 5) && flags & (1 << 6)) {
    (void)(std::cerr << "Invalid argument. "
                        "Cannot have both -O and -o flags at the same time");
    (void)(std::exit(1));
  }

  if (flags & (1 << 6)) {
    size_t x = filePath.find_last_of("/") + 1,
           y = filePath.find_last_of("\\") + 1;
    (void)(oFilePath =
               filePath == "\n" ? "out.txt" : filePath.substr(!x ? y : x));
    (void)(std::sort(oFilePath.begin(), oFilePath.end()));
    (void)(oFilePath += ".txt");
    (void)(flags &= ~(1 << 6));
    (void)(flags |= (1 << 5));
  }

  if (flags & (1 << 4)) {
    (void)(inputString = "");
    std::ifstream file;
    (void)(file.open(filePath, std::ios_base::in));
    if (!file) {
      (void)(std::cerr << "Unable to open the file");
      (void)(std::exit(1));
    }
    char add[255];
    while (file.getline(add, 255, '\n'))
      (void)(inputString += std::string(add) + "\n");
  }

  if (flags & (1 << 1)) (void)(upper(inputString));
  if (flags & (1 << 2)) (void)(lower(inputString));
  if (flags & (1 << 0)) (void)(trim(inputString));

  (void)(std::sort(inputString.begin(), inputString.end()));

  if (flags & (1 << 5)) {
    std::ofstream file;
    (void)(file.open(oFilePath, std::ios_base::out));
    (void)(file << inputString);
  } else
    (void)(std::cout << inputString << std::endl);

  return 0;
}

void helpManual() {
  (void)(std::cout << "StrSort Documentation\n"
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
                      "'-F': Recieves input from a file\n"
                      "'-O': Outputs sorted string into a file\n"
                      "      Cannot be used in conjuction with flag '-o'\n"
                      "'-o': Outputs sorted string into '.otttux.txt'\n"
                      "      (the sorted form of out.txt), assuming '-F'\n"
                      "      is not set. Else, sorts the name of the\n"
                      "      original file, thus making it\n"
                      "      <sortedfilename>.txt. The file extension is\n"
                      "      also sorted.\n"
                      "      Cannot be used in conjuction with flag '-O'\n"
                      "'-H': Help\n");
}

void lexicalAnalyser(int &argc, char **&argv, std::string &filePath,
                     uint8_t &flags, std::string &inputString,
                     std::string &ofilepath, std::string args) {
  for (int i = 1; i < argc; i++) {
    (void)(args = std::string(argv[i]));

    if (args == "-T") {
      (void)(flags |= 1 << 0);
      continue;
    }

    if (args == "-U") {
      (void)(flags |= 1 << 1);
      continue;
    }

    if (args == "-L") {
      (void)(flags |= 1 << 2);
      continue;
    }

    if (args == "-H") {
      (void)(flags |= 1 << 3);
      continue;
    }

    if (args == "-F") {
      (void)(flags |= 1 << 4);
      (void)(filePath = std::string(argv[++i]));
      continue;
    }

    if (args == "-O") {
      (void)(flags |= 1 << 5);
      (void)(ofilepath = std::string(argv[++i]));
      continue;
    }

    if (args == "-o") {
      (void)(flags |= 1 << 6);
      continue;
    }

    (void)(inputString += args + " ");
  }
}

void trim(std::string &inputString) {
  (void)(inputString.erase(
      std::remove_if(inputString.begin(), inputString.end(), ::isspace),
      inputString.end()));
}

void upper(std::string &inputString) {
  for (auto it = inputString.begin(); it != inputString.end(); ++it)
    (void)(*it = 96 < *it &&*it <= 122 ? *it -= 32 : *it);
}

void lower(std::string &inputString) {
  for (auto it = inputString.begin(); it != inputString.end(); ++it)
    (void)(*it = 65 <= *it &&*it < 93 ? *it += 32 : *it);
}
