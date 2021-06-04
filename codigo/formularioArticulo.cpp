#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream htmlFile;
    string line = "";
    string hilera = getenv("HTTP_COOKIE");
    // Insertar header en el body
    htmlFile.open("../html/headerInsert.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Content-Type: text/html\n\n";
        while(getline(htmlFile, line)){
            if(line.find("Login") == string::npos && line.find("</ul>") == string::npos && line.find("fa-shopping-cart") == string::npos){
                cout << line << "\n";
            }
            else{
                if(line.find("</ul>") != string::npos){
                    if(hilera.find("estadoUsuario=Registrado") != string::npos){
                        cout << "<li class=\"nav-item\">";
                    cout<< "<a class=\"nav-link\" href=\"formularioArticulo.cgi\">Agregar articulo</a></li></ul>";
                    } else{
                    cout << "</ul> \n";
                    }
                }
                if(line.find("Login") != string::npos){
                    if(hilera.find("estadoUsuario=Registrado") != string::npos){
                        string botonCerrarSesion = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Cerrar sesion</a>";
                    cout << botonCerrarSesion << "\n";
                    }else{
                        string botonLoginRegistro = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Login/Registro</a>";
                        cout << botonLoginRegistro << "\n";
                    }
                }
                if(line.find("fa-shopping-cart") != string::npos){
                    if(hilera.find("estadoUsuario=Registrado") != string::npos){
                        cout << "<a href='carritoCompra.cgi' class='btn btn-outline-success my-2 my-sm-0'> <i class='fa fa-shopping-cart fa-2x'></i> </a> \n";
                    }
                }
            }
        }
        htmlFile.close();
        
        // Insertar contenido en el body
        htmlFile.open("../html/formularioArticulo.html");
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
