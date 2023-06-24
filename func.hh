#ifndef STRSORT_FUNC_HH
#define STRSORT_FUNC_HH

void helpManual();
uint8_t lexicalAnalyser(int &, char **&, std::string &, std::string &,
                        std::string &, std::string args = "",
                        uint8_t flags = 0);
void trim(std::string &);
void upper(std::string &);
void lower(std::string &);

#endif