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

    // Nombre
    string nombre = queryString.substr(0,queryString.find("&correoInput",0));
    nombre = nombre.substr(nombre.find("nombreInput=")+12);
    parameterCheckerPtr->checkParameter(nombre);
    

    // Correo electronico
    string  correo = queryString.substr(0,queryString.find("&asunto",0));
    correo = correo.substr(correo.find("correoInput=")+11);
    parameterCheckerPtr->checkParameter(correo);

    // Asunto
    string  asunto = queryString.substr(0,queryString.find("&contenido",0));
    asunto = asunto.substr(asunto.find("asunto=")+7);
    parameterCheckerPtr->checkParameter(asunto); 

    // Contenido
    string contenido = queryString.substr(queryString.find("contenidoInput=")+15);
    parameterCheckerPtr->checkParameter(contenido);

    //Usuario
    string hilera = getenv("HTTP_COOKIE");
    string usuario = hilera.substr(0, hilera.find("; estado"));
    usuario = usuario.substr(usuario.find("correo=")+7);
    parameterCheckerPtr->checkParameter(usuario);

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

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
                        cout << "<a href='carritoCompra.html' class='btn btn-outline-success my-2 my-sm-0'> <i class='fa fa-shopping-cart fa-2x'></i> </a> \n";
                    }
                }
            }
        }
        htmlFile.close();
         con = conectorModularPtr->connection();
        if(hilera.find("estadoUsuario=Registrado") == string::npos){
            string query = "INSERT INTO Formulario(nombre,correo,asunto,contenido) VALUES ('" + nombre + "','" + correo + "','" + asunto + "','" + contenido + "');";
            res = conectorModularPtr->query(con, query.c_str());
             //clean up the database result
        	mysql_free_result(res);  
             //close database connection
            mysql_close(con);
            cout << "El formulario fue enviado exitosamente." << "<br>";
        }else{
            string query = "INSERT INTO Formulario(nombre,correo,asunto,contenido) VALUES ('" + nombre + "','" + correo + "','" + asunto + "','" + contenido + "','"+ usuario + "');";
            res = conectorModularPtr->query(con, query.c_str());
            //clean up the database result
            mysql_free_result(res);  
            //close database connection
            mysql_close(con);
            
            cout << "El formulario fue enviado exitosamente." << "<br>";
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