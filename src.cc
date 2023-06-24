#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "func.hh"

#define trimSpaces (1 << 0)
#define upperCase (1 << 1)
#define lowerCase (1 << 2)
#define help (1 << 3)
#define fileIn (1 << 4)
#define fileOut (1 << 5)
#define fileout (1 << 6)

int main(int argc, char **argv) {
  std::string oFilePath, filePath = "\n", inputString;
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
  uint8_t flags = lexicalAnalyser(argc, argv, filePath, inputString, oFilePath);

  if (flags & help) {
    helpManual();
    std::exit(0);
  }

  if (flags & upperCase && flags & lowerCase) {
    std::cerr << "Invalid argument. "
                 "Cannot have both -U and -L flags at same time";
    std::exit(1);
  }

  if (flags & fileOut && flags & fileout) {
    std::cerr << "Invalid argument. "
                 "Cannot have both -O and -o flags at the same time";
    std::exit(1);
  }

  if (flags & fileout) {
    size_t x = filePath.find_last_of("/") + 1,
           y = filePath.find_last_of("\\") + 1;
    oFilePath = filePath == "\n" ? "out.txt" : filePath.substr(!x ? y : x);
    std::sort(oFilePath.begin(), oFilePath.end());
    oFilePath += ".txt";
    flags &= ~fileOut;
    flags |= fileOut;
  }

  if (flags & fileIn) {
    inputString = "";
    std::ifstream file;
    file.open(filePath, std::ios_base::in);
    if (!file) {
      std::cerr << "Unable to open the file";
      std::exit(1);
    }
    try {
      std::string add;
      while (std::getline(file, add)) inputString += add + "\n";
    } catch (const std::length_error &lenE) {
      std::cout << "You have hit the limit of the free service. "
                   "Please sign up for our subscription for more characters "
                   "per execution\n"
                   "This is a joke.\n"
                   "Debugging details:\n"
                << lenE.what();
      std::exit(1);
    }
  }

  if (flags & upperCase) upper(inputString);
  if (flags & lowerCase) lower(inputString);
  if (flags & trimSpaces) trim(inputString);

  std::sort((inputString).begin(), (inputString).end());

  if (flags & fileOut) {
    std::ofstream file;
    file.open(oFilePath, std::ios_base::out);
    file << inputString;
  } else
    std::cout << inputString << std::endl;

  return 0;
}

void helpManual() {
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
               "'-H': Help\n";
}

uint8_t lexicalAnalyser(int &argc, char **&argv, std::string &filePath,
                        std::string &inputString, std::string &ofilepath,
                        std::string args, uint8_t flags) {
  for (int i = 1; i < argc; i++) {
    args = std::string(argv[i]);

    if (args == "-T") {
      flags |= trimSpaces;
      continue;
    }

    if (args == "-U") {
      flags |= upperCase;
      continue;
    }

    if (args == "-L") {
      flags |= lowerCase;
      continue;
    }

    if (args == "-H") {
      flags |= help;
      continue;
    }

    if (args == "-F") {
      flags |= fileIn;
      filePath = std::string(argv[++i]);
      continue;
    }

    if (args == "-O") {
      flags |= fileOut;
      ofilepath = std::string(argv[++i]);
      continue;
    }

    if (args == "-o") {
      flags |= fileout;
      continue;
    }

    inputString += args + " ";
  }
  return flags;
}

void trim(std::string &inputString) {
  inputString.erase(
      std::remove_if(inputString.begin(), inputString.end(), ::isspace),
      inputString.end());
}

void upper(std::string &inputString) {
  for (auto it = inputString.begin(); it != inputString.end(); ++it)
    *it = 96 < *it && *it <= 122 ? *it -= 32 : *it;
}

void lower(std::string &inputString) {
  for (auto it = inputString.begin(); it != inputString.end(); ++it)
    *it = 65 <= *it && *it < 93 ? *it += 32 : *it;
}
