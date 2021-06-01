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

        // Insertar contenido en el body
        htmlFile.open("../html/carritoCompra.html");
        if(!htmlFile.is_open()) {
            cout << "<TITLE>Failure</TITLE>\n";
            cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
        }
        else {
            line = "";
            while(getline(htmlFile, line)){
                cout << line +"\n";
            }

            char *hilera = getenv("HTTP_COOKIE");
            //cout << hilera;

            /*string Str = "";
            Str =+ hilera;*/

            //string str(hilera);

            //cout << hilera;

            
            string s;
            stringstream ss;
            ss << hilera;
            s = ss.str();

            //cout << s;


            /*
             strncpy (pch,"123456789",6);
              cout << pch << '\n';*/



            /*string str="We think in generalities, but we live in details.";
            size_t pos = str.find("live");
            string str2 = str.substr (pos,5);
            cout << str2;*/

            size_t pos = s.find("articulo");     

            string str3 = s.substr (pos+9);   
              
            size_t posfin = str3.find(";");    

            string str4 = str3.substr (0,posfin); 

            //cout << str4 << '\n';


            
            
            vector<string> result;
            stringstream s_stream(str4); //create string stream from the string
            while(s_stream.good()) {
              string substr;
              getline(s_stream, substr, ','); //get first string delimited by comma
              result.push_back(substr);
           }

            /*for(int i = 0; i<result.size(); i++) {    //print all splitted strings
                cout << result.at(i) << endl;
            }
*/

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


            
              

            //string str4 = str3.substr(0,posfin); 

            //cout << str4 << '\n';


            /*char* sublis = substr(hilera,9, 15);
            char* chars_array = strtok(sublis, ",");


            cout << "<table class=\"table\">\n";
            cout << "<thead>";
            cout << "<th>Articulos</th>";
            cout << "</thead>";
            cout << "<tbody>";
            while (chars_array)
            {
                cout << "<tr>";
                cout << "<td>" << chars_array << "</td>";
                cout << "</tr>";
                chars_array = strtok(NULL, ",");
            }
            cout << "</tbody>";
            cout << "</table>\n";
        
            cout << "</body>\n";
            cout << "</html>\n";*/
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

