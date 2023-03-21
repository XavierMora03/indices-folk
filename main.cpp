#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "archivo_datos.h"
#include "contribuyentes_struct.h"
#include "interfaz.h"

using namespace std;
int main(int argc, char *argv[]) {
  contribuyente contr;
  Interfaz InterfazObj;
  ArchivoDatos Archivo;

  Archivo.inicializaArchivo();

  contr = InterfazObj.altaRegistro();
  Archivo.escribirContribuyente(contr);
  return 0;
}
