#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream htmlFile;
    htmlFile.open("../html/loginRegistro.html");
    //htmlFile.open("../html/header.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
	cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
    }
    htmlFile.close();
    return 0;
}
