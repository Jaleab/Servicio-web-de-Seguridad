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
        string correo = getenv("QUERY_STRING");
        //cout << correo << "<br>";
        if(correo.find("ucr.ac.cr") != string::npos){
            cout << "Set-Cookie:estado = registrado;\r\n";
        }
        else{
            cout << "Set-Cookie:estado = noRegistrado;\r\n";
        }
        cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
        htmlFile.close();
        cout << getenv("HTTP_COOKIE") << "<br>";
        string hilera = getenv("HTTP_COOKIE");
        if(hilera.find("estado=registrado") != string::npos){
            cout << "Usuario esta registrado <br>";
        }
        else{
            cout << "El usuario no esta registrado <br>";
        }
    }
    return 0;
}

