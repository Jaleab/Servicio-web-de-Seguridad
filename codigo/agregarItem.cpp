// g++ `mysql_config --cflags --libs` agregarItem.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/agregarItem.cgi -std=c++11
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Checker.h"
#include "ConectorModular.h"
using namespace std;

char* substr(char* arr, int begin, int len)
{
    char* res = new char[len + 1];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}

vector<string> split(string data, string separator)
{
    vector<string> resul;
    int end = data.find(separator);
    int start = 0;
    while (end != -1)
    {
        resul.push_back(data.substr(start, end - start));
        start = end + separator.size();
        end = data.find(separator, start);
    }
    resul.push_back(data.substr(start, end - start));

    return resul;
}

int main(int argc, char* argv[], char** envp) {
    // Parameters checker
    Checker* parameterCheckerPtr;

    string hilera = getenv("HTTP_COOKIE");
    string queryString = getenv("QUERY_STRING");
    string infoArticulo = queryString.substr(queryString.find("id=")+3);
    string nuevoCarrito = "";
    string query = "";
    string nombre = "";

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
        if(hilera.find("estadoUsuario=Registrado") != string::npos && parameterCheckerPtr->checkNumber(infoArticulo)){
            ConectorModular* conectorModularPtr;
            MYSQL* con;
            MYSQL_RES *res; // the results
            MYSQL_ROW row;  // the results rows (array)

            con = conectorModularPtr->connection();
            query = "SELECT nombre FROM Articulo WHERE articuloId = " + infoArticulo;
            res = conectorModularPtr->query(con, query.c_str());
            row = mysql_fetch_row(res);
            nombre = row[0];
	//    string nombre = "Bicicleta";

	    // clean up the database result
	    //mysql_free_result(res);
	    
	    // close database connection
	    mysql_close(con);

            // Append producto en cookie
            if(hilera.find("articulo=vacio") != string::npos){
                cout << "Set-Cookie: articulo="+ nombre +"\r\n";
            }
            else{
                nuevoCarrito = hilera.substr(hilera.find("articulo=")+9,hilera.find(";")-1);
                nuevoCarrito += "," + nombre;
                cout << "Set-Cookie: articulo="+nuevoCarrito+"\r\n";
            }

            cout << "Content-Type: text/html\n\n";
            cout << "<TITLE>Login</TITLE>\n";
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
        }  
        else{
            cout << "<p style='text-align: center;> Ingrese al sistema en Login/Registro. </p><br>";
        }      
        htmlFile.close();

	// Insertar contenido en el body

	/*cout << query << "<br>";
	cout << nuevoCarrito;*/
	cout << "<iframe src='carritoCompra.cgi' style='display: block; border:none; height:1100px; width:1100px;' title='carrito'></iframe>";

        /*htmlFile.open("../html/carritoCompra.html");
        if(!htmlFile.is_open()) {
            cout << "<TITLE>Failure</TITLE>\n";
            cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
        }
        else {
            line = "";
            while(getline(htmlFile, line)){
                cout << line +"\n";
	    }
       }
       htmlFile.close();*/

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



