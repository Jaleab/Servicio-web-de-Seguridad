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

   string Checker::urlDecode(string str){
    string ret;
    char ch;
    int i, ii, len = str.length();

    for (i=0; i < len; i++){
        if(str[i] != '%'){
            if(str[i] == '+')
                ret += ' ';
            else
                ret += str[i];
        }else{
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
    }
    return ret;
}

