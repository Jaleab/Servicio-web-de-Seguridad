// g++ `mysql_config --cflags --libs` resultadoBusqueda.cpp ConectorModular.cpp -o ../cgi-bin/resultadoBusqueda.cgi
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ConectorModular.h"
using namespace std;

int main(int argc, char* argv[], char** envp) {

    string queryString = getenv("QUERY_STRING");
    string criterioBusqueda;

    if(queryString.length()>12){
        criterioBusqueda = queryString.substr(queryString.find("searchInput=")+12);
    }

    

    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res; // the results
    MYSQL_ROW row;  // the results rows (array)


if(!criterioBusqueda.empty()){
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
            cout << line +"\n";
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
                cout << "<a href='http://172.24.131.136/cgi-bin/articulo.cgi?id="; // Cambiar el IP por el de servidor.  id = articulo Id
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
            cout << "Criterio de búsqueda no ha devuelto resultado";
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
