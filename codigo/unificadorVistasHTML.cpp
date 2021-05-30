 #include "unificadorVistasHTML.h"
 #include "lectorArchivoHTML.h"

void unificadorVistasHTML::mostrarVistaCompleta(string bodyHTML){
    lectorArchivoHTML lectorHTML;
    ifstream htmlFile;
    
    htmlFile.open("../html/headerInsert.html");
    cout << "Content-Type:text/html\n";
    if(!htmlFile.is_open()) {
        lectorHTML.enviarMensajeError();
        
    }
    else {
        lectorHTML.leerContenidoHTML(htmlFile);
        htmlFile.close();
        
        htmlFile.open("../html/"+bodyHTML);
        if(!htmlFile.is_open()) {
        lectorHTML.enviarMensajeError();
        
        }
        else {   
            lectorHTML.leerContenidoHTML(htmlFile);
            htmlFile.close();

            htmlFile.open("../html/footerInsert.html");
            if(!htmlFile.is_open()) {
            lectorHTML.enviarMensajeError();
            
            }
            else {
                lectorHTML.leerContenidoHTML(htmlFile);
                htmlFile.close();
            }
        }
    }
}