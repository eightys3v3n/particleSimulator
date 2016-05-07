#ifndef PARSE_
#define PARSE_

#include <iostream>

struct FindResult
{
  int position = -1;
  int length = -1;
};

bool isNumber(char character);
bool isLetter(char character);
FindResult find(std::string source, std::string pattern);

#endif // PARSE_