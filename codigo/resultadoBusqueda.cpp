// g++ `mysql_config --cflags --libs` resultadoBusqueda.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/resultadoBusqueda.cgi -std=c++11
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
    string criterioBusqueda;
    string hilera = getenv("HTTP_COOKIE");

    // Parameters checker
    Checker* parameterCheckerPtr;

    if(queryString.length()>12){
        criterioBusqueda = queryString.substr(queryString.find("searchInput=")+12);
    }

    

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res; // the results
    MYSQL_ROW row;  // the results rows (array)


if(!criterioBusqueda.empty()){
    parameterCheckerPtr->checkParameter(criterioBusqueda);
    con = conectorModularPtr->connection();
    string query = "SELECT * FROM Articulo WHERE nombre LIKE '%"+ criterioBusqueda +"%';";
    res = conectorModularPtr->query(con, query.c_str());


}
else{
    con = conectorModularPtr->connection();
    string query = "SELECT * FROM Articulo ORDER BY articuloId desc LIMIT 5;";
    res = conectorModularPtr->query(con, query.c_str());
}

    ifstream htmlFile;
    string line = "";
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
        
        int count = 0;

        if(res){

            while ((row = mysql_fetch_row(res)))
            {
                ++count;
                cout << "<div class='card' style='width: 100rem; margin-top: 15px; margin-left:10%; padding: 10px;'>";
                cout << "<div class='card-body'>";
                cout << "<h5 class='card-title'>";
                cout << row[1];
                cout << "</h5>";
                cout << "<p class='card-text'>";
                cout << row[4];
                cout << "</p>";
                cout << "<a href='articulo.cgi?id="; //id = articulo Id
                cout << row[0];
                cout <<"' class='btn btn-primary float-right'>Detalle</a>";  
                cout << "<p class='card-text'>";
                cout << row[3];
                cout << "</p>";
                cout << "</div>";
                cout << "</div>";

            }

            // clean up the database result
            mysql_free_result(res);
            
            // close database connection
            mysql_close(con);

        } 
        if(count==0) {
            cout << "<p style= 'text-align: center'>Criterio de búsqueda no ha devuelto resultado</p>";
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
    //}
    }
    return 0;
}

