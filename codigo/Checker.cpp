#include "Checker.h"
#include <string>
#include <algorithm>
using namespace std;

   void Checker::checkParameter(string& parameter){
      // Le quite and, union y el espacio en blanco " ".
      string key[11] = {"*","=","%0a","%","/","|","&","^" ,"#","/*","*/" };
      for (int i = 0; i < 11; ++i){
         if(parameter.find(key[i]) != string::npos){
		for(char letter : key[i]){
			parameter.erase(remove(parameter.begin(), parameter.end(), letter), parameter.end());
		}
         }
      }
   }

