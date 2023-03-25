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

  string menu = "MENU\n1-Agregar\n2-Consulta\n9-Salir\nSeleccione una opcion: ";

  char option;
  while (option != '9') {
    cout << menu;
    cin >> option;

    switch (option) {
    case '1': {
      cout << "Alta" << endl;
      contribuyente nuevoCont = Interfaz.altaRegistro();
      ArchivoDatos.escribirContribuyente(nuevoCont);
      IndicePrimario.insertar(nuevoCont.rfc, 43);
      break;
    }

    case '2': {
      cout << "Consulta" << endl;
      int tipoIndice;
      cout << "1-Principal (RFC)\n2-Secundario (CIUDAD)\nSeleccion el tipo de "
              "indice: ";
      cin >> tipoIndice;
      getchar();
      if (tipoIndice == 1) {
        string rfc;
        cout << "Introdusca el RFC a consultar: ";
        getline(cin, rfc);
        // lo pasamos a mayusculas
        for (int i = 0; i < rfc.size(); i++) {
          rfc[i] = toupper(rfc[i]);
        }
        int indice = IndicePrimario.consultaIndice(rfc);
        if (indice == -1) {
          cout << "NO EXISTE LA LLAVE CON RFC: " << rfc << endl;
          break;
        }
        Interfaz

      } else if (tipoIndice == 2) {

      } else {
        cout << "Tipo de indice no valido" << endl;
      }
    }
    }
  }

  /*
    while (i-- > 0) {
      contribuyente cont = Interfaz.altaRegistro();
      ArchivoDatos.escribirContribuyente(cont);
      IndicePrimario.insertar(cont.rfc, 1);
    }
  */

  return 0;
}
