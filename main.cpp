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

string autoFixText(string data) {
  int sizeS = data.size();
  for (int aux(0); aux < sizeS; aux++) {
    data[aux] = toupper(data[aux]);
  }
  return data;
}

void addRegister() {
  contribuyente rCont;
  int auxI(0), iData(0);
  char auxC;
  string auxS, dateAux;

  system("cls");
  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | REGISTRO | "
          ">--->>-->>-->>-->>--|\n";
  cout << "\n\n\t\t\t\tINGRESE EL NOMBRE --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 33) {
    auxS = auxS.erase(33, iData);
  }
  auxS = autoFixText(auxS);
  strcpy(rCont.nombre, auxS.c_str());

  cout << "\n\t\t\t\tINGRESE EL APELLIDO PATERNO --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 33) {
    auxS = auxS.erase(33, iData);
  }
  auxS = autoFixText(auxS);
  strcpy(rCont.apellido[0], auxS.c_str());

  cout << "\n\t\t\t\tINGRESE EL APELLIDO MATERNO --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 33) {
    auxS = auxS.erase(33, iData);
  }
  auxS = autoFixText(auxS);
  strcpy(rCont.apellido[1], auxS.c_str());

  cout << "\n\t\t\t\tTELEFONO --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 13) {
    auxS = auxS.erase(13, iData);
  }
  strcpy(rCont.telefono, auxS.c_str());

  cout << "\n\t\t\t\tCIUDAD --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 33) {
    auxS = auxS.erase(33, iData);
  }
  auxS = autoFixText(auxS);
  strcpy(rCont.ciudad, auxS.c_str());

  cout << "\n\t\t\t\tDIRECCION --> ";
  fflush(stdin);
  getline(cin, auxS);
  iData = auxS.size();
  if (iData >= 44) {
    auxS = auxS.erase(44, iData);
  }
  auxS = autoFixText(auxS);
  strcpy(rCont.direccion, auxS.c_str());

  cout << "\n\t\t\t\t--[FECHA DE NACIMIENTO]--\n";
  cout << "\n\t\t\t\tANIO DE NACIMIENTO --> ";
  fflush(stdin);
  getline(cin, auxS);
  dateAux = auxS + '/';

  cout << "\n\t\t\t\tMES DE NACIMIENTO --> ";
  fflush(stdin);
  getline(cin, auxS);
  dateAux += auxS + '/';

  cout << "\n\t\t\t\tDIA DE NACIMIENTO --> ";
  fflush(stdin);
  getline(cin, auxS);
  dateAux += auxS;
  cout << "\n\t\t\t\tFECHA DE NACIMIENTO: " << dateAux;
  iData = dateAux.size();
  if (iData >= 11) {
    dateAux = dateAux.erase(11, iData);
  }
  strcpy(rCont.fechaNacimiento, dateAux.c_str());

  cout << "\n\n\t\t\t\tESTADO CIVIL (C(Casado) o S(Soltero) --> ";
  fflush(stdin);
  cin >> auxC;
  if (auxC == 'C' or auxC == 'S') {
  } else {
    if (auxC == 'c' or auxC == 's') {
      if (auxC == 'c') {
        auxC = 'C';
      } else {
        auxC = 'S';
      }
    } else {
      cout << "\n\t\t\t\tSOLTERO POR DEFAULT\n";
      auxC = 'S';
    }
  }
  rCont.estadoCivil = auxC;

  cout << "\n\t\t\t\tDEPENDIENTES --> ";
  fflush(stdin);
  cin >> auxI;
  rCont.dependientes = auxI;

  auxS = generateKey(rCont);
  iData = auxS.size();
  if (iData >= 13) {
    auxS = auxS.erase(13, iData);
  }
  strcpy(rCont.rfc, auxS.c_str());

  cout << "\nRFC: " << rCont.rfc;
  cout << "\nNombre: " << rCont.nombre;
  cout << "\nApellido Paterno: " << rCont.apellido[0];
  cout << "\nApellido Materno: " << rCont.apellido[1];
  cout << "\nTelefono: " << rCont.telefono;
  cout << "\nCiudad: " << rCont.ciudad;
  cout << "\nDireccion: " << rCont.direccion;
  cout << "\nFecha De Nacimiento: " << rCont.fechaNacimiento;
  cout << "\nEstado Civil: " << rCont.estadoCivil;
  cout << "\nDependiente: " << rCont.dependientes;

  cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | REGISTRADO | "
          ">--->>-->>-->>-->>--|\n\n\n\t\t\t";
  system("pause");
}

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
    addRegister();
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
  adminMenu();
  return 0;
}
