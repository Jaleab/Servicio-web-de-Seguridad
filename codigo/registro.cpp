// g++ `mysql_config --cflags --libs` registro.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/registro.cgi -std=c++11
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ConectorModular.h"
#include "Checker.h"
using namespace std;

int main(int argc, char const *argv[]){
    string queryString = getenv("QUERY_STRING");
    string hilera = getenv("HTTP_COOKIE");

    // Chequeador de parametros
    Checker* parameterCheckerPtr;
    queryString = parameterCheckerPtr->urlDecode(queryString);
    //replace(queryString.begin(), queryString.end(),'+',' ');	

    // Nombre
    string nombre = queryString.substr(0,queryString.find("&apellido1Input",0));
    nombre = nombre.substr(nombre.find("nombreInput=")+12);
    parameterCheckerPtr->checkParameter(nombre);
    

    // Apellido1
    string apellido1 = queryString.substr(0,queryString.find("&apellido2Input",0));
    apellido1 = apellido1.substr(apellido1.find("apellido1Input=")+15);
    parameterCheckerPtr->checkParameter(apellido1);

    // Apellido2
    string apellido2 = queryString.substr(0,queryString.find("&usuarioInput",0));
    apellido2 = apellido2.substr(apellido2.find("apellido2Input=")+15);
    parameterCheckerPtr->checkParameter(apellido2);

    // Usuario
    string usuario = queryString.substr(0, queryString.find("&correoInput",0));
    usuario = usuario.substr(usuario.find("usuarioInput=")+13);
    parameterCheckerPtr->checkParameter(usuario);

    // Correo electronico
    string correo = queryString.substr(0,queryString.find("&telefonoInput",0));
    correo = correo.substr(correo.find("correoInput=")+10);
    correo[correo.find("%40")] = '@';
    correo = correo.erase(correo.find("@40")+1,2);
    parameterCheckerPtr->checkParameter(correo);

    // Telefono
    string telefono = queryString.substr(0, queryString.find("&claveInput",0));
    telefono = telefono.substr(telefono.find("telefonoInput=")+14);
    parameterCheckerPtr->checkParameter(telefono);

    // Clave
    string clave = queryString.substr(queryString.find("claveInput=")+11);
    parameterCheckerPtr->checkParameter(clave);

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
            cout << "Set-Cookie:correo = nulo;\r\n";
        }
        else{
            cout << "Set-Cookie:estadoUsuario = Registrado;\r\n";
            cout << "Set-Cookie:correo = " + correo  + ";\r\n";
        }
        cout << "Content-Type: text/html; charset=utf-8\n\n";
        cout << "<TITLE>Registro</TITLE>\n";
        while(getline(htmlFile, line)){
            if(line.find("Login") == string::npos && line.find("</ul>") == string::npos && line.find("fa-shopping-cart") == string::npos){
                cout << line << "\n";
            }
            else{
                if(line.find("</ul>") != string::npos){
                    if(estaRegistrado == '0'){
                        cout << "<li class=\"nav-item\">";
                        cout<< "<a class=\"nav-link\" href=\"formularioArticulo.cgi\">Agregar articulo</a></li></ul>";
                    } else{
                        cout << "</ul> \n";
                    }
                }
                if(line.find("Login") != string::npos){
                    if(estaRegistrado == '0'){
                        string botonCerrarSesion = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Cerrar sesion</a>";
                        cout << botonCerrarSesion << "\n";
                    }else{
                        string botonLoginRegistro = "<a href=\"loginRegistro.cgi\" class=\"btn btn-outline-success my-2 my-sm-0\">Login/Registro</a>";
                        cout << botonLoginRegistro << "\n";
                    }
                }
                if(line.find("fa-shopping-cart") != string::npos){
                    if(estaRegistrado == '0'){
                        cout << "<a href='carritoCompra.cgi' class='btn btn-outline-success my-2 my-sm-0'> <i class='fa fa-shopping-cart fa-2x'></i> </a> \n";
                    }
                }
            }
        }
        htmlFile.close();
        if(estaRegistrado == '0'){
	    cout << "<p style='text-align: center;'> El usuario fue registrado exitosamente.</p>" << "<br>";
        }
        else{
	    cout << "<p style='text-align: center;'>El usuario ya esta registrado.</p>" << "<br>";
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


