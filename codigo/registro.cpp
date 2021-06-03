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
	
    // Nombre
    string nombre = queryString.substr(0,queryString.find("&apellido1Input",0));
    nombre = nombre.substr(nombre.find("nombreInput=")+12);

    // Apellido1
    string apellido1 = queryString.substr(0,queryString.find("&apellido2Input",0));
    apellido1 = apellido1.substr(apellido1.find("apellido1Input=")+15);

    // Apellido2
    string apellido2 = queryString.substr(0,queryString.find("&usuarioInput",0));
    apellido2 = apellido2.substr(apellido2.find("apellido2Input=")+15);

    // Usuario
    string usuario = queryString.substr(0, queryString.find("&correoInput",0));
    usuario = usuario.substr(usuario.find("usuarioInput=")+13);

    // Correo electronico
    string correo = queryString.substr(0,queryString.find("&telefonoInput",0));
    correo = correo.substr(correo.find("correoInput=")+12);
    correo[correo.find("%40")] = '@';
    correo = correo.erase(correo.find("@40")+1,2);

    // Telefono
    string telefono = queryString.substr(0, queryString.find("&claveInput",0));
    telefono = telefono.substr(telefono.find("telefonoInput=")+14);

    // Clave
    string clave = queryString.substr(queryString.find("claveInput=")+11);

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    con = conectorModularPtr->connection();

    // Verificar si el usuario ya esta registrado con correo y clave
    string query = "SELECT count(*) FROM Usuario WHERE correo ='"+ correo + "' AND usuario = '" + usuario + "';";
    res = conectorModularPtr->query(con, query.c_str());
    row = mysql_fetch_row(res);
    char estaRegistrado = *row[0];

    if(estaRegistrado == '0'){
	// clean up the database result
    mysql_free_result(res);
        query = "INSERT INTO Usuario(correo,nombre,appelido1,apellido2,telefono,usuario,clave) VALUES ('" + correo + "','" + nombre + "','" + apellido1 + "','" + apellido2 + "','" + telefono + "','" + usuario + "','" + clave + "');";
	res = conectorModularPtr->query(con, query.c_str());
    }
    // clean up the database result
    mysql_free_result(res);    
    // close database connection
    mysql_close(con);

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
	if(estaRegistrado != '0'){
                cout << "Set-Cookie:estadoUsuario = NoRegistrado;\r\n";
        }
        else {
                cout << "Set-Cookie:estadoUsuario = Registrado;\r\n";
        }
	cout << "Content-Type: text/html\n\n";
        cout << "<TITLE>Registro</TITLE>\n";
        while(getline(htmlFile, line)){
            if(line.find("Login") == string::npos){
                cout << line << "\n";
            }
            else{
		string hilera = getenv("HTTP_COOKIE");
                if(estaRegistrado != '0'){
                    string botonCerrarSesion = "<a href=\"https://172.24.131.152/cgi-bin/loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Login/Registro</a>";
                    cout << botonCerrarSesion << "\n";
                }
                else{
                    string botonLoginRegistro = "<a href=\"https://172.24.131.152/cgi-bin/loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Cerrar sesion</a>";
                    cout << botonLoginRegistro << "\n";
                }
            }
        }
        htmlFile.close();

	if(estaRegistrado == '1'){
		cout << "El usuario ya esta registrado." << "<br>";
	}
	else{
		cout << "El usuario fue registrado exitosamente." << "<br>";
	}
    }
    return 0;
}
