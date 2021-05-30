#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[], char** envp) {
    ifstream htmlFile;
    htmlFile.open("../html/formularioArticulo.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        
        int posicion = 0;
       // string datos = getenv("QUERY_STRING");
       string datos ="Nombre=Principito&Precio=5000&Descripcion=Libro";
        string separadorCamposFormulario ="&";
        string separadorValores = "=";
        string valor;
        vector<std::string> vectorDatos(3);
        while((posicion = datos.find(separadorValores))!= string::npos){
            datos.erase(0, posicion+separadorValores.length());
            int posicionSeparadorCampos = datos.find(separadorCamposFormulario);
            valor = datos.substr(0,posicionSeparadorCampos);
            cout<<valor<<endl;
        }
        //metodo para separar las hileras
        cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
        htmlFile.close();
    }
    return 0;
}

