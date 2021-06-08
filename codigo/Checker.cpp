#include "Checker.h"
#include <string>
#include <algorithm>
#include <unordered_set>
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
   
   bool Checker::checkNumber(const string& number){
	unordered_set<char> digits {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	for(char digit : number){
	     if(digits.find(digit) == digits.end()){
		   return false;
	     }
	}
  	return true;
   }

