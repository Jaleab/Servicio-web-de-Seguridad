// g++ `mysql_config --cflags --libs` login.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/login.cgi -std=c++11
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ConectorModular.h"
#include "Checker.h"
using namespace std;

int main(int argc, char* argv[], char** envp) {
    string queryString = getenv("QUERY_STRING");

    // Parameters checker
    Checker* parameterCheckerPtr;
	
    // Correo electronico
    string correo = queryString.substr(0,queryString.find("&claveInput",0));
    correo = correo.substr(correo.find("correoInput=")+12);
    correo[correo.find("%40")] = '@';
    correo = correo.erase(correo.find("@40")+1,2);
    parameterCheckerPtr->checkParameter(correo);

    // Clave
    string clave = queryString.substr(queryString.find("claveInput=")+11);
    parameterCheckerPtr->checkParameter(clave);

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res; // the results
    MYSQL_ROW row;  // the results rows (array)

    con = conectorModularPtr->connection();
    string query = "SELECT count(*) FROM Usuario WHERE correo ='"+ correo + "' AND clave = '" + clave + "';";
    res = conectorModularPtr->query(con, query.c_str());
    row = mysql_fetch_row(res);
    char estaRegistrado = *row[0];
    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);

    // Cookies estado usuario
    if(estaRegistrado == '0'){
        cout << "Set-Cookie:estadoUsuario = NoRegistrado;\r\n";
    }
    else{
	    cout << "Set-Cookie:correo = " + correo  + ";\r\n";
            cout << "Set-Cookie:estadoUsuario = Registrado;\r\n";
    }


    ifstream htmlFile;
    string line = "";
    // Insertar header en el body
    htmlFile.open("../html/headerInsert.html");
    if(!htmlFile.is_open()){
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Content-Type: text/html\n\n";
        cout << "<TITLE>Login</TITLE>\n";
        while(getline(htmlFile, line)){
            if(line.find("Login") == string::npos){
                cout << line << "\n";
            }
            else{
                if(estaRegistrado == '1'){
                    string botonCerrarSesion = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Cerrar sesión</a>";
                    cout << botonCerrarSesion << "\n";
                }
                else{
                    string botonLoginRegistro = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Login/Registro</a>";
                    cout << botonLoginRegistro << "\n";
                }
            }
        }
        htmlFile.close();
	if(estaRegistrado == '0'){
		cout << "Ingreso credenciales incorrectos" << "<br>";
	}
	else{
		cout << "Ingreso correctamente al sistema." << "<br>";
	}

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
    return 0;
}


