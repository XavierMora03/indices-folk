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
  IndicePrimario.imprimirRegistros();

  /*
    while (i-- > 0) {
      contribuyente cont = Interfaz.altaRegistro();
      ArchivoDatos.escribirContribuyente(cont);
      IndicePrimario.insertar(cont.rfc, 1);
    }
    */
  stIndiceRfc a("aaaaAA", 43), b("zzzzz", 43);
  cout << "velda: " << (b < a);
  return 0;
}
