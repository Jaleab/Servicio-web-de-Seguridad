// g++ `mysql_config --cflags --libs` finCheckout.cpp ConectorModular.cpp Checker.cpp -o cgi-bin/finCheckout.cgi -std=c++11
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include "Checker.h"
#include "ConectorModular.h"
using namespace std;


// Return this number if it is a single digit, otherwise,
// return the sum of the two digits
int getDigit(int number)
{
  if (number < 9)
    return number;
  return number / 10 + number % 10;
}
 
// Return the number of digits in d
int getSize(long d)
{
  string num = to_string(d);
  return num.length();
}
 
// Return the first k number of digits from
// number. If the number of digits in number
// is less than k, return number.
long getPrefix(long number, int k)
{
  if (getSize(number) > k)
  {
    string num = to_string(number);
    return stol(num.substr(0, k));
  }
  return number;
}
 
// Return true if the digit d is a prefix for number
bool prefixMatched(long number, int d)
{
  return getPrefix(number, getSize(d)) == d;
}
 
// Get the result from Step 2
int sumOfDoubleEvenPlace(long int number)
{
  int sum = 0;
  string num = to_string(number) ;
  for (int i = getSize(number) - 2; i >= 0; i -= 2)
    sum += getDigit(int(num[i] - '0') * 2);
 
  return sum;
}
 
// Return sum of odd-place digits in number
int sumOfOddPlace(long number)
{
  int sum = 0;
  string num = to_string(number) ;
  for (int i = getSize(number) - 1; i >= 0; i -= 2)
    sum += num[i] - '0';
  return sum;
}
 
// Return true if the card number is valid
bool isValid(long int number)
{
  return (getSize(number) >= 13 &&
          getSize(number) <= 16) &&
    (prefixMatched(number, 4) ||
     prefixMatched(number, 5) ||
     prefixMatched(number, 37) ||
     prefixMatched(number, 6)) &&
    ((sumOfDoubleEvenPlace(number) +
      sumOfOddPlace(number)) % 10 == 0);
}

int main(int argc, char const *argv[]){
    string queryString = u8"";
    queryString = getenv("QUERY_STRING");

    // Chequeador de parametros
    Checker* parameterCheckerPtr;	
    queryString = parameterCheckerPtr->urlDecode(queryString);
    replace(queryString.begin(), queryString.end(),'+',' ');

    // Direccion
    string direccion = queryString.substr(0,queryString.find("&provincia",0));
    direccion = direccion.substr(direccion.find("direccion=")+10);
    parameterCheckerPtr->checkParameter(direccion);
    

    // Provincia
    string provincia = queryString.substr(0,queryString.find("&nombreTarjeta",0));
    provincia = provincia.substr(provincia.find("&provincia=")+11);
    parameterCheckerPtr->checkParameter(provincia);

    // nombreTarjeta
    string nombreTarjeta = queryString.substr(0,queryString.find("&numeroTarjeta",0));
    nombreTarjeta = nombreTarjeta.substr(nombreTarjeta.find("&nombreTarjeta=")+14);
    parameterCheckerPtr->checkParameter(nombreTarjeta);

    // numeroTarjeta
    string numeroTarjeta = queryString.substr(0,queryString.find("&mesExp",0));
    numeroTarjeta = numeroTarjeta.substr(numeroTarjeta.find("&numeroTarjeta=")+15);
    parameterCheckerPtr->checkParameter(numeroTarjeta);

    // mesExp
    string mesExp = queryString.substr(0,queryString.find("&anoExp",0));
    mesExp = mesExp.substr(mesExp.find("&mesExp=")+7);
    parameterCheckerPtr->checkParameter(mesExp);

    // anoExp
    string anoExp = queryString.substr(0,queryString.find("&cvv",0));
    anoExp = anoExp.substr(anoExp.find("&anoExp=")+7);
    parameterCheckerPtr->checkParameter(anoExp);

    // CVV
    string cvv = queryString.substr(queryString.find("&cvv")+4);
    parameterCheckerPtr->checkParameter(cvv);

    // Cliente
    string hilera = getenv("HTTP_COOKIE");
    string cliente = hilera.substr(0, hilera.find("; estado"));
    cliente = cliente.substr(cliente.find("correo=")+7);
    parameterCheckerPtr->checkParameter(cliente);

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
	string tempNumero = "";
        if(hilera.find("estadoUsuario=Registrado") == string::npos){
            cout << "<p style='text-align: center;'> Inicie sesion para realizar la compra de articulos. </p>" << "<br>";
        }else{
	    tempNumero = numeroTarjeta;
	    tempNumero.erase(remove(tempNumero.begin(), tempNumero.end(), '-'), tempNumero.end());
	    std::string::size_type sz;
	    long numero = stol(tempNumero, &sz);
	    if(isValid(numero) && stoi(anoExp) >= 2021 && cvv.length() == 3){
            con = conectorModularPtr->connection();
            string query = "INSERT INTO Compra(fecha,cliente) VALUES(NOW(), '" + cliente + "');";
            res = conectorModularPtr->query(con, query.c_str());
            //clean up the database result
            mysql_free_result(res);  
            //close database connection
            mysql_close(con);
	    cout << "<p style:'align-text: center'>Los datos de la tarjeta ingresada fueron validados correctamente. La compra fue finalizada correctamente.</p>" << "<br>";
	    }
	    cout << direccion << " " << provincia << " " << nombreTarjeta << " " << numeroTarjeta << " " << mesExp << " " << anoExp << " " << cvv << "<br>";
	    cout << tempNumero << "<br>";

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
