#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string ENV[ 24 ] = {
   "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
   "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
   "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
   "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
   "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
   "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
   "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
   "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
   "SERVER_SIGNATURE","SERVER_SOFTWARE" };   

const int HTTP_COOKIE = 10;

int main(int argc, char* argv[], char** envp) {
    ifstream htmlFile;
    htmlFile.open("/var/www/Servicio-web-de-Seguridad/html/usuarioVerificado.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Set-Cookie:estado = registrado;\r\n";
        cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
            cout << line +"\n";
        }
    cout << "\n\n\n\n\n";
    htmlFile.close();
    // Cookies esta en el indice 10 de envp
    cout << envp[HTTP_COOKIE] << "<br>";
    int i = 0;
    // Recorrido en las variables de ambiente
    for (char **env = envp; *env != 0; env++){
        char *thisEnv = *env;
        cout << i++ << " " << thisEnv << "<br>";
     }	
}
return 0;
}

