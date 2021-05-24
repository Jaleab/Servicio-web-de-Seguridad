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

int main(int argc, char* argv[]) {
    ifstream htmlFile;
    htmlFile.open("/var/www/Servicio-web-de-Seguridad/html/loginRegistro.html");
    if(!htmlFile.is_open()) {
        cout << "Content-Type:text/html\n";
        cout << "<TITLE>Failure</TITLE>\n";
        cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
    }
    else {
        cout << "Content-Type: text/html\n\n";
        string line = "";
        while(getline(htmlFile, line)){
        cout << line +"\n";
    }
    htmlFile.close();
     for ( int i = 0; i < 24; i++ ) {
      cout << "<tr><td>" << ENV[ i ] << "</td><td>";
      
      // attempt to retrieve value of environment variable
      char *value = getenv( ENV[ i ].c_str() );  
      if ( value != 0 ) {
         cout << value;                                 
      } else {
         cout << "Environment variable does not exist.";
      }
      cout << "</td></tr>\n";
   }	
}
return 0;
}
