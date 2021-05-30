#include "lectorArchivoHTML.h"

void lectorArchivoHTML::enviarMensajeError(){
    cout << "<TITLE>Failure</TITLE>\n";
    cout << "<P><EM>Unable to open data file, sorry!</EM>\n";
}
void lectorArchivoHTML::leerContenidoHTML(ifstream &htmlFile){
    string line = "";
    while(getline(htmlFile, line)){
        cout << line +"\n";
    }
}