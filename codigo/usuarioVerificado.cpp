#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[], char** envp) {
    ifstream htmlFile;
    htmlFile.open("../html/usuarioVerificado.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Set-Cookie:estado = registrado;\r\n";
        cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
    cout << "\n\n\n\n\n";
    htmlFile.close();
    cout << getenv("HTTP_COOKIE") << "<br>";
    }
    return 0;
}

