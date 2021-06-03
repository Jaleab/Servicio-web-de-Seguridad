#include "Checker.h"
#include <string>
#include <algorithm>
using namespace std;

   void Checker::checkParameter(string& parameter){
      string key[14] = {"and","*","="," ","%0a","%","/","union","|","&","^" ,"#","/*","*/" };
      for (int i = 0; i < 14; ++i){
         if(parameter.find(key[i]) != string::npos){
		for(char letter : key[i]){
			parameter.erase(remove(parameter.begin(), parameter.end(), letter), parameter.end());
		}
		//cout << parameter << "<br> <br>";
         }
      }
   }

