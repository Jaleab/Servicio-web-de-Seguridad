#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "unificadorVistasHTML.h"
using namespace std;

int main(int argc, char* argv[]) {
    unificadorVistasHTML unificadorVista;
    unificadorVista.mostrarVistaCompleta("articulo.html");
    return 0;
}