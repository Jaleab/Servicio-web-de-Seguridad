#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
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
    

    ifstream htmlFile;
    string line = "";
    string hilera = getenv("HTTP_COOKIE");
    // Insertar header en el body
    htmlFile.open("../html/headerInsert.html");

    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Content-type:text/html\r\n";
	//cout << "Set-Cookie: z=a\r\n";
        //cout << "Set-Cookie: articulo=taza,carro,pais,moto,tina,helio,colchones;\r\n";
        //cout << "Set-Cookie: user=tizio;\r\n";
        cout << "Set-Cookie: password=profdfosfiotjrejiod;\r\n\r\n";
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
}
   cout << "<html>\n";
   cout << "<body>\n";

        /*char *hilera = (char*)malloc(1000);
        hilera = getenv("HTTP_COOKIE");*/

        vector<string> listaCookies = split(hilera, ";");
        vector<string> articulosCookie;
        vector<string> articulos;
        for (int i = 0; i < listaCookies.size(); ++i)
        {
            if(listaCookies[i].find("articulo=") != -1){
                
                articulosCookie.push_back(split(listaCookies[i],"=")[1]);
            }
        }
        articulos = split(articulosCookie[0],",");


            cout << "<div class=\"card card3\" style=\"width: 50rem; margin-top: 30px; margin-left:20%\">\n";
            cout << "<div class=\"card-body\">\n";

            cout << "<table class=\"table\">\n";
            cout << "<thead>";
            cout << "<th>Articulos</th>";
            cout << "</thead>";
            cout << "<tbody>";
            for(int i = 0; i < articulos.size(); i++) {    //print all splitted strings
                                cout << "<tr>";
                cout << "<td>" << articulos[i] << "</td>";
                cout << "</tr>";
            }
            cout << "</tbody>";
            cout << "</table>\n";

	   string total = hilera.substr(hilera.find("total=")+6);
	   total = total.substr(0,total.find(";"));
           cout << " <hr> <p>Total <span class='price' style='color:black'><b>"+ total + "</b></span> colones</p>\n";

            cout << "</body>\n";
            cout << "</html>\n";

            cout << "<div style=\"text-align:center;\">\n";
            cout << "<a href='resultadoBusqueda.cgi' id=\"btn_Regresar\" class=\"btn btn-primary\" style=\"width: 200px;\">Regresar</a>\n";
	    if(articulosCookie[0] != "vacio"){
                 cout << "<a href='checkout.cgi'  id=\"btn_FinalizarCompra\" class=\"btn btn-primary\" style=\"width: 200px;\">Realizar compra</a>\n";
	    }
            cout << "</div>\n";
/*
            //<!-- Modal -->
            cout << "<div class=\"modal fade\" id=\"myModal\" role=\"dialog\">";
            cout << "<div class=\"modal-dialog\">";
    
            //<!-- Modal content-->
            cout << "<div class=\"modal-content\">";
            cout << "<div class=\"modal-header\">";
            //cout << "Set-Cookie: articulo=comida,rice;";
            cout << "<button type=\"button\" class=\"close\" data-dismiss=\"modal\">&times;</button>";
            cout << "<h4 class=\"modal-title\">Aviso de compra</h4>";
            cout << "</div>";
            cout << "<div class=\"modal-body\">";
            cout << "<p>Compra realizada exitosamente.</p>";
            cout << "</div>";
            cout << "<div class=\"modal-footer\">";
            cout << "<button onclick=\"window.location.href='http://localhost/cgi-bin/carritoCompra.cgi';\" type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\">Cerrar</button>";
            cout << "</div>";
            cout << "</div>";
            cout << "</div>";
            cout << "</div>";
            //<!-- Modal Fin-->*/

            cout << "</div>\n";
            cout << "</div>\n";



        

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

    return 0;
}


