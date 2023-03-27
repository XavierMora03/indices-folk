#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "archivo_datos.h"
#include "contribuyentes_struct.h"
#include "indicePrimario.h"
#include "indiceSecundario.h"
#include "interfaz.h"

using namespace std;

Interfaz Interfaz;
IndicePrimario IndicePrimario(NOMBRE_ARCHIVO_INDICE_PRIMARIO);
IndiceSecundario IndiceSecundario(NOMBRE_ARCHIVO_INDICE_SECUNDARIO);
ArchivoDatos ArchivoDatos(NOMBRE_ARCHIVO_DATOS);

void adminMenu() {
  system("Title AUTOMAXX");
  setlocale(LC_ALL, "spanish");
  fflush(stdin);
  int v1;
  system("cls");

  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | MENU | >--->>-->>-->>-->>--|\n";
  cout << "\n\n\t\t\t\tAGREGAR REGISTRO\t[1]";
  cout << "\n\n\t\t\t\tBUSCAR REGISTRO\t\t[2]";
  cout << "\n\n\t\t\t\tSALIR\t\t\t[3]";
  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | <<>> | >--->>-->>-->>-->>--|";
  cout << "\n\n\t\t\tINGRESE LA OPCION DESEADA --> ";

  cin >> v1;
  getchar();
  switch (v1) {
    case 1: {
      cout << "AGREGAR CONTRIBUYENTE\n";
      contribuyente cont = Interfaz.altaRegistro();
      int error_llaveExiste = IndicePrimario.insertar(cont.rfc);
      if (error_llaveExiste == -1) {
        cout << "La llave ya existe, saliendo de añadir." << endl;
        break;
      }
      // como ya probamos que no exsite, lo añadirmos al archivo de datos
      ArchivoDatos.escribirContribuyente(cont);
      // tambien lo escribimos al Indice secundario
      IndiceSecundario.insertar(cont.ciudad, cont.rfc);
      adminMenu();
      break;
    }
    case 2: {
      cout << "CONSULTA\n";
      int consultaOpcion;
      cout << "1 para consulta por RFC\n2 para consulta por CIUDAD: ";
      cin >> consultaOpcion;
      if (consultaOpcion == 1) {
        string rfcStr;
        cout << "Introdusca la llave: ";
        int dir = IndicePrimario.consultaIndice(rfcStr);
        // en dado case de que la llave no exsista
        if (dir == -1) {
          break;
        }
        // llegamos aca, entonces si exsite
        contribuyente registroAConsultar = ArchivoDatos.dameContribuyente(dir);
        // e imprimimos
        Interfaz.mostrarRegistro(registroAConsultar);
      }
      if (consultaOpcion == 2) {
      }
      adminMenu();
      break;
    }
    case 3:
      system("cls");
      cout << "\n\n\n\n\t\t\t|--<<--<<--<<--<<---< | SALIENDO... | "
              ">--->>-->>-->>-->>--|";
      exit(0);
      break;

    default:
      adminMenu();
      break;
  }
}

int main() {
  IndiceSecundario.verLista();
  int i = 3;
  while (i-- > 0) {
    contribuyente cont = Interfaz.altaRegistro();
    IndicePrimario.insertar(cont.rfc);
    IndiceSecundario.insertar(cont.ciudad, cont.rfc);
  }
  // adminMenu();
  return 0;
}
