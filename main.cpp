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

  char v1;
  system("cls");

  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | MENU | >--->>-->>-->>-->>--|\n";
  cout << "\n\n\t\t\t\tAGREGAR REGISTRO\t[1]";
  cout << "\n\n\t\t\t\tBUSCAR REGISTRO\t\t[2]";
  cout << "\n\n\t\t\t\tSALIR\t\t\t[3]";
  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | <<>> | >--->>-->>-->>-->>--|";
  cout << "\n\n\t\t\tINGRESE LA OPCION DESEADA --> ";

  cin >> v1;

  switch (v1) {

  case '1':
    adminMenu();
    break;

  case '2':
    // aqui va la busqueda();
    adminMenu();
    break;

  case '3':
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
  int i = 3;
  while (i-- > 0) {
    contribuyente cont = Interfaz.altaRegistro();
    Interfaz.mostrarRegistro(cont);
    int dir = IndicePrimario.insertar(cont.rfc);
    if (dir == -1)
      break;
    ArchivoDatos.escribirContribuyente(cont);
    IndiceSecundario.insertar(cont.ciudad, cont.rfc, dir);
  }
  cout << "IMPRIMIENTO WE" << endl;
  IndiceSecundario.verLista();
  // adminMenu();
  return 0;
}
