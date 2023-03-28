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

Interfaz interfaz;
IndicePrimario indicePrimario(NOMBRE_ARCHIVO_INDICE_PRIMARIO);
IndiceSecundario indiceSecundario(NOMBRE_ARCHIVO_INDICE_SECUNDARIO);
ArchivoDatos archivoDatos(NOMBRE_ARCHIVO_DATOS);

void adminMenu() {
  // system("Title AUTOMAXX");
  // setlocale(LC_ALL, "spanish");
  fflush(stdin);
  int v1;
  // system("cls");

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
      contribuyente cont = interfaz.altaRegistro();
      int error_llaveExiste = indicePrimario.insertar(cont.rfc);
      if (error_llaveExiste == -1) {
        cout << "La llave ya existe, saliendo de añadir." << endl;
        break;
      }
      // como ya probamos que no exsite, lo añadirmos al archivo de datos
      archivoDatos.escribirContribuyente(cont);
      // tambien lo escribimos al Indice secundario
      indiceSecundario.insertar(cont.ciudad, cont.rfc);
      adminMenu();
      break;
    }
    case 2: {
      cout << "CONSULTA\n";
      int consultaOpcion;
      cout << "1 para consulta por RFC\n2 para consulta por CIUDAD: ";
      cin >> consultaOpcion;
      getchar();
      if (consultaOpcion == 1) {
        string rfcStr;
        cout << "Introdusca la llave: ";
        getline(cin, rfcStr);

        int dir = indicePrimario.consultaIndice(rfcStr);
        // en dado case de que la llave no exsista
        if (dir == -1) {
          break;
        }
        // llegamos aca, entonces si exsite
        // una vez que tenemos la direccion, mostramos el regisrto que esta en
        // esa direccion
        archivoDatos.muestraContribuyente(dir);
      }
      if (consultaOpcion == 2) {
        cout << "INTRODUSCA LA CIUDAD\n";
        string ciudad;
        getline(cin, ciudad);
        indiceSecundario.consultaIndice(ciudad);
      }
      adminMenu();
      break;
    }
    case 3:
      // system("cls");
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
  // indiceSecundario.verLista();
  /*
    int i = 3;
    while (i-- > 0) {
      contribuyente cont = Interfaz.altaRegistro();
      IndicePrimario.insertar(cont.rfc);
      ArchivoDatos.escribirContribuyente(cont);
      IndiceSecundario.insertar(cont.ciudad, cont.rfc);
    }
  */
  adminMenu();
  return 0;
}
