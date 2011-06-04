/*! \file string_utils.h
 */

#include "string_utils.h"

namespace numlib{ namespace io{

void stripWhiteSpace(String & s, const char* whitespace)
{
	 Size len = s.length();

	 for(const char* w = whitespace; *w != '\0'; ++w)
	 {
		  Size pos = 0;
		  while(pos < len)
		  {
			   while(s[pos] == *w)
					s.erase(pos,1);
			   ++pos;
		  }
	 }
}

void stripComments(String & s, char cc)
{
	 Size pos;
	 pos = s.find(cc);
	 if(pos != String::npos)
		  s.erase(pos);
}

bool split(const String & line, String & substr1, String & substr2, const char* delim)
{
	 Size pos1;
	 Size pos2;
	 Size len = std::strlen(delim);

	 pos1 = line.find(delim);
	 if(pos1 == String::npos)
		 return true;
		
	 pos2 = pos1+len;
	 substr1 = line.substr(0,pos1);
	 substr2 = line.substr(pos2);

	 return false;
}

}}//::numlib::io
