#ifndef _CHECKER
#define _CHECKER
#include <string>
#include <iostream>
using namespace std;

class Checker {
   public:
      void checkParameter(string&);
      bool checkNumber(const string&);
      string urlDecode(string);
};
#endif

