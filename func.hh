#ifndef STRSORT_FUNC_HH
#define STRSORT_FUNC_HH

void helpManual();
void lexicalAnalyser(int &, char **&, std::string &, uint8_t &, std::string &,
                     std::string &, std::string args = "");
void trim(std::string &);
void upper(std::string &);
void lower(std::string &);

#endif