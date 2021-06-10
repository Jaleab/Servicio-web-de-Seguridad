// g++ `mysql_config --cflags --libs` articulo.cpp ConectorModular.cpp Checker.cpp -o ../cgi-bin/articulo.cgi -std=c++11
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

    string queryString; 
    string infoArticulo;
    string hilera = getenv("HTTP_COOKIE");

    // Parameters checker
    Checker* parameterCheckerPtr;

    queryString = getenv("QUERY_STRING");
    infoArticulo = queryString.substr(queryString.find("id=")+3);

    

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
        cout << "Content-Type: text/html; charset=utf-8\n\n";
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

            ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res; // the results
    MYSQL_ROW row;  // the results rows (array)

    if(parameterCheckerPtr->checkNumber(infoArticulo)){
    con = conectorModularPtr->connection();
    string query = "SELECT * FROM Articulo WHERE articuloId ='"+infoArticulo+"';";
    res = conectorModularPtr->query(con, query.c_str());

    row = mysql_fetch_row(res);

            // Insertar contenido en el body
        cout << "<div class='card card3' style='width: 50rem; margin-top: 30px; margin-left:20%'>";
        cout << "<div class='card-body'>";
        cout << "<div>";
        cout << "<div class='row'>";
        cout << "<div class='col'>";
        cout << "<div class='form-group'>";
        cout << "<label class='col-form-label' for='nombreArticuloInput'>Nombre del artículo</label>";
        cout << "<input type='text' title='Nombre del articulo' class='form-control' placeholder='";
        cout << row[1];
        cout << "'id=nombreArticuloInput disabled>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div>";
        cout << "<div class='row'>";
        cout << "<div class='col'>";
        cout << "<div class='form-group'>";
        cout << "<label class='col-form-label' for='autorArticuloInput'>Autor del artículo</label>";
        cout << "<input type='text' title='Autor del articulo' class='form-control' placeholder='";
        cout << row[4];
        cout << "'id=autorArticuloInput disabled>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div>";
        cout << "<div class='row'>";
        cout << "<div class='col'>";
        cout << "<div class='form-group'>";
        cout << "<label class='col-form-label' for='descripcionInput'>Descripción del artículo</label>";
        cout << "<textarea title='Descripción del articulo' class='form-control' placeholder='";
        cout << row[2];
        cout << "' id='descripcionInput' disabled></textarea>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div>";
        cout << "<div class='row'>";
        cout << "<div class='col'>";
        cout << "<div class='form-group'>";
        cout << "<label class='col-form-label' for='precioInput'>Precio del artículo</label>";
        cout << "<input type='text' title='Precio del artículo' class='form-control' placeholder='";
        cout << row[3];
        cout << "' id='precioArticuloInput' disabled>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div style='text-align:center;'>";
        cout << "<a class='btn btn-primary' style='width: 200px;display:inline-block' href='resultadoBusqueda.cgi'>Regresar</a>";
        cout << "<a class='btn btn-primary' style='width: 200px;display:inline-block' href='agregarItem.cgi?id=";
        cout << row[0];
        cout << "'>Agregar</a>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";

            // clean up the database result
            mysql_free_result(res);
            
            // close database connection
            mysql_close(con);
    }
    else{
        cout << "<p style= 'text-align: center'>No se metan alli!!!!</p>";
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


