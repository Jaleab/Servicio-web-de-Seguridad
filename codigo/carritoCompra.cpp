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


int main(int argc, char* argv[], char** envp) {
    

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
        cout << "Content-type:text/html\r\n";
        cout << "Set-Cookie: articulo=taza,carro,pais,moto,tina,helio,colchones;\r\n";
        cout << "Set-Cookie: user=tizio;\r\n";
        cout << "Set-Cookie: password=profdfosfiotjrejiod;\r\n\r\n";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
        htmlFile.close();


   cout << "<html>\n";
   cout << "<body>\n";


            char *hilera = getenv("HTTP_COOKIE");

            
            string s;
            stringstream ss;
            ss << hilera;
            s = ss.str();


            size_t pos = s.find("articulo");     

            string str3 = s.substr (pos+9);   
              
            size_t posfin = str3.find(";");    

            string str4 = str3.substr (0,posfin); 


            
            
            vector<string> result;
            stringstream s_stream(str4); //create string stream from the string
            while(s_stream.good()) {
              string substr;
              getline(s_stream, substr, ','); //get first string delimited by comma
              result.push_back(substr);
           }


            cout << "<div class=\"card card3\" style=\"width: 50rem; margin-top: 30px; margin-left:20%\">\n";
            cout << "<div class=\"card-body\">\n";

            cout << "<table class=\"table\">\n";
            cout << "<thead>";
            cout << "<th>Articulos</th>";
            cout << "</thead>";
            cout << "<tbody>";
            for(int i = 0; i<result.size(); i++) {    //print all splitted strings
                                cout << "<tr>";
                cout << "<td>" << result.at(i) << "</td>";
                cout << "</tr>";
            }
            cout << "</tbody>";
            cout << "</table>\n";
        
            cout << "</body>\n";
            cout << "</html>\n";

            cout << "<div>\n";
            cout << "<div class=\"row\">\n";
            cout << "<div class=\"col\">\n";

            cout << "<div class=\"form-group\" style=\"text-align:center;\">\n";
            cout << "<label class=\"col-form-label\" for=\"TotalInput\">Total:</label>\n";
            cout << "<input title=\"Total\" class=\"form-control\" placeholder=\"0\" id=\"TotalInput\" disabled></textarea>\n";
            cout << "</div>\n";
            cout << "</div>\n";
            cout << "</div>\n";
            cout << "</div>\n";

            cout << "<div style=\"text-align:center;\">\n";
            cout << "<button id=\"btn_Regresar\" type=\"button\" class=\"btn btn-primary\" style=\"width: 200px;\">Regresar</button>\n";
            cout << "<button id=\"btn_FinalizarCompra\" type=\"button\" data-toggle=\"modal\" data-target=\"#myModal\" class=\"btn btn-primary\" style=\"width: 200px;\">Finalizar compra</button>\n";
            cout << "</div>\n";

            //<!-- Modal -->
            cout << "<div class=\"modal fade\" id=\"myModal\" role=\"dialog\">";
            cout << "<div class=\"modal-dialog\">";
    
            //<!-- Modal content-->
            cout << "<div class=\"modal-content\">";
            cout << "<div class=\"modal-header\">";
            cout << "<button type=\"button\" class=\"close\" data-dismiss=\"modal\">&times;</button>";
            cout << "<h4 class=\"modal-title\">Aviso de compra</h4>";
            cout << "</div>";
            cout << "<div class=\"modal-body\">";
            cout << "<p>Compra realizada exitosamente.</p>";
            cout << "</div>";
            cout << "<div class=\"modal-footer\">";
            cout << "<button type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\">Cerrar</button>";
            cout << "</div>";
            cout << "</div>";
            cout << "</div>";
            cout << "</div>";
            //<!-- Modal Fin-->

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
}

    return 0;
}

