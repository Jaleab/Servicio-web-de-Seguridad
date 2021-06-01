// g++ `mysql_config --cflags --libs` registro.cpp ConectorModular.cpp -o ../cgi-bin/registro.cgi
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ConectorModular.h"
using namespace std;

int main(int argc, char const *argv[]){
    string queryString = getenv("QUERY_STRING");
	
	// Usuario
    string usuario = queryString.substr(0,queryString.find("&apellido1Input",0));
    usuario = usuario.substr(usuario.find("correoInput=")+13);

    // Clave
    string clave = queryString.substr(queryString.find("nombreInput=")+11);

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

// https://172.24.131.152/cgi-bin/registro.cgi?nombreInput=Ricardo&apellido1Input=Villalon&apellido2Input=Fonseca&usuarioInput=Villa&telefonoInput=77777777&claveInput=Hacker1234
/* INSERT INTO Usuario(correo, nombre, appelido1, apellido2, telefono, usuario, contraseña) VALUES('javier.abarca@ucr.ac.cr','Javier','Abarca','Jimenez','12345678','Jaleab','1234678');
Verificar campos de la base de datos Appelido1******
*/
/*
    con = conectorModularPtr->connection();
    res = conectorModularPtr->query(con, "SELECT COUNT(*) FROM Usuario WHERE usuario = 'Jaleab' AND clave = '1234678';");
    // clean up the database result
    mysql_free_result(res);    
    // close database connection
    mysql_close(con);
*/
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
		string hilera = getenv("HTTP_COOKIE");
		char estaRegistrado = hilera.find("estadoUsuario=Registrado") != string::npos?'1':'0';
                if(estaRegistrado == '1'){
                    string botonCerrarSesion = "<a href=\"https://172.24.131.152/cgi-bin/cerrarSesion.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Cerrar sesión</a>";
                    cout << botonCerrarSesion << "\n";
                }
                else{
                    string botonLoginRegistro = "<a href=\"https://172.24.131.152/cgi-bin/loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Login/Registro</a>";
                    cout << botonLoginRegistro << "\n";
                }
            }
        }
        htmlFile.close();

        cout << usuario;
    }
    return 0;
}

