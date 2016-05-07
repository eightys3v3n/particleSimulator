#include <iostream>
#include "parse.hpp"

bool isNumber(char character)
{
	if ( (int)character > 47 && (int)character < 59 )
		return true;

	return false;
}

bool isLetter(char character)
{
	if ( (int)character > 64 && (int)character < 92 )
		return true;
	else if ( (int)character > 96 && (int)character < 124 )
		return true;

	return false;
}

FindResult find(std::string source, std::string pattern)
{
  int space = 0;
	FindResult result;

  for (unsigned int s = 0; s < source.length(); s++)
  {
    for (unsigned int p = 0; p < pattern.length(); p++)
    {
      if (s + p >= source.length())
        break;

      if (pattern[p] == '~')
      {
        if (p < pattern.length() - 1)
        {
          p++;

          if (pattern[p] == '~' || pattern[p] == '*')
            return result;

          if ((space = find(source.substr(s + p + space), std::string(1, pattern[p])).position) == -1)
            break;
        }
        else
          space = source.length() - 1 - (p + s);
      }
      else if (source[s + p + space] != pattern[p] && pattern[p] != '*')
        break;

      if (p >= pattern.length() - 1)
			{
				result.position = s;
				result.length = p + space + 1;
        return result;
			}
    }
  }

  return result;
}