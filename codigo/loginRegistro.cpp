#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream htmlFile;
    string hilera = getenv("HTTP_COOKIE");
    string line = "";
    // Insertar header en el body
    htmlFile.open("../html/headerInsert.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
	cout << "Set-Cookie:estadoUsuario = NoRegistrado;\r\n";
	cout << "Set-Cookie:correo = nulo;\r\n";
	cout << "Set-Cookie:articulo = vacio;\r\n";
        cout << "Content-Type: text/html\n\n";
        while(getline(htmlFile, line)){
            if(line.find("fa-shopping-cart") == string::npos){
                cout << line << "\n";
            }
            else{
                if(line.find("fa-shopping-cart") != string::npos){
                    if(hilera.find("estadoUsuario=Registrado") != string::npos){
                        cout << "<a href='carritoCompra.html' class='btn btn-outline-success my-2 my-sm-0'> <i class='fa fa-shopping-cart fa-2x'></i> </a> \n";
                    }
                }
            }
        }
        htmlFile.close();
        
        // Insertar contenido en el body
        htmlFile.open("../html/loginRegistro.html");
        if(!htmlFile.is_open()) {
            cout << "<TITLE>Failure</TITLE>\n";
            cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
        }
        else {
            line = "";
            while(getline(htmlFile, line)){
                cout << line +"\n";
            }
            htmlFile.close();

            // Insertar footer en el body
            htmlFile.open("../html/footerInsert.html");
            if(!htmlFile.is_open()) {
                cout << "<TITLE>Failure</TITLE>\n";
                cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
            }
            else {
                line = "";
                while(getline(htmlFile, line)){
                    cout << line +"\n";
                }
                htmlFile.close();
            }
        }
    }
    return 0;
}
