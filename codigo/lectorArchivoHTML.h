#ifndef _LECTORARCHIVOHTML
#define _LECTORARCHIVOHTML
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class lectorArchivoHTML {
    public:
    void enviarMensajeError();
    void leerContenidoHTML(ifstream &);
   
};
#endif