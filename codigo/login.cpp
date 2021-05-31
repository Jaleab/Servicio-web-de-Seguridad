// g++ `mysql_config --cflags --libs` login.cpp ConectorModular.cpp -o ../cgi-bin/login.cgi
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
	
	// Correo electronico
        string correo = queryString.substr(0,queryString.find("&claveInput",0));
        correo = correo.substr(correo.find("correoInput=")+12);
        correo[correo.find("%40")] = '@';
        correo = correo.erase(correo.find("@40")+1,2);

        // Clave
        string clave = queryString.substr(queryString.find("%3D=")+4);

        ConectorModular* conectorModularPtr;
        MYSQL* con;
        MYSQL_RES *res; // the results
        MYSQL_ROW row;  // the results rows (array)

        con = conectorModularPtr->connection();
        string query = "SELECT count(*) FROM Usuario WHERE correo ='"+ correo + "' AND clave = '" + clave + "';";
        res = conectorModularPtr->query(con, query.c_str());
        row = mysql_fetch_row(res);
	char estaRegistrado = *row[0];


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
            cout << line +"\n";
        }
        htmlFile.close();

        // Correo electronico
        string correo = queryString.substr(0,queryString.find("&claveInput",0));
        correo = correo.substr(correo.find("correoInput=")+12);
	correo[correo.find("%40")] = '@';
	correo = correo.erase(correo.find("@40")+1,2);
        cout << "Correo: " << correo << "<br>";

	// Clave
	string clave = queryString.substr(queryString.find("%3D=")+4);
        cout << "Clave: " << clave << "<br>";

	cout << query << "<br>";
	if(row && estaRegistrado == '1'){
		cout << "Usuario registrado" << "<br>";
	}
	else{
		cout << "Usuario n oesta registrado" << "<br>";
	}
    }
    return 0;
}

