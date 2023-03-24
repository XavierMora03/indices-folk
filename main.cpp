#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "archivo_datos.h"
#include "contribuyentes_struct.h"
#include "indicePrimario.h"
#include "interfaz.h"

using namespace std;
int main(int argc, char *argv[]) {
  Interfaz Interfaz;
  ArchivoDatos ArchivoDatos(NOMBRE_ARCHIVO_DATOS);
  IndicePrimario IndicePrimario(NOMBRE_ARCHIVO_INDICE_PRIMARIO);
  int i = 3;
  while (i-- > 0) {
    ArchivoDatos.inicializaArchivo();
    IndicePrimario.inicializaArchivo();
    contribuyente cont = Interfaz.altaRegistro();
    ArchivoDatos.escribirContribuyente(cont);
    IndicePrimario.insertar(cont.rfc, 1);
  }
  return 0;
}
