// g++ `mysql_config --cflags --libs` informacionArticuloAgregado.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/informacionArticuloAgregado.cgi -std=c++11
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include "Checker.h"
#include "ConectorModular.h"
using namespace std;
int main(int argc, char const *argv[]){
    string queryString = getenv("QUERY_STRING");
    replace(queryString.begin(), queryString.end(),'+',' ');

    // Chequeador de parametros
    Checker* parameterCheckerPtr;	

    // NombreArticulo
    string articulo = queryString.substr(0,queryString.find("&precioArticulo",0));
    articulo = articulo.substr(articulo.find("nombreArticulo=")+15);
    parameterCheckerPtr->checkParameter(articulo);
    

    // PrecioArticulo
    string precio = queryString.substr(0,queryString.find("&descripcionArticulo",0));
    precio = precio.substr(precio.find("precioArticulo=")+15);
    parameterCheckerPtr->checkParameter(precio);

    // DescripcionArticulo
    string descripcion = queryString.substr(queryString.find("descripcionArticulo=")+20);
    parameterCheckerPtr->checkParameter(descripcion);

    // PropietarioArticulo
   // string hilera = getenv("HTTP_COOKIE");
    string propietario= "yerlin@correo.com";
    //string propietario = hilera.find("correo=");

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    con = conectorModularPtr->connection();

    string query = "INSERT INTO Articulo(nombre,precio,descripcion,propietario) VALUES ('" + articulo + "','" + precio + "','" + descripcion + "','" + propietario + "');";

    res = conectorModularPtr->query(con, query.c_str());

    //clean up the database result
    mysql_free_result(res);  
    //close database connection
    mysql_close(con);

    ifstream htmlFile;
    string line = "";
    string hilera = getenv("HTTP_COOKIE");
    // Insertar header en el body
    htmlFile.open("../html/headerInsert.html");
    if(!htmlFile.is_open()){
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
	cout << "Content-Type: text/html\n\n";
        while(getline(htmlFile, line)){
            if(line.find("Login") == string::npos){
                cout << line << "\n";
            }
            else{
		        
                if(hilera.find("estado=Registrado") == string::npos){
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

        cout << queryString << "<br>";
        cout << query << "<br>";
        cout << "El articulo fue agregado exitosamente." << "<br>";
    }
	
    return 0;
}
