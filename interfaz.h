// my_class.h
#ifndef INTERFAZ_H  // include guard
#define INTERFAZ_H

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "contribuyentes_struct.h"
using namespace std;
class Interfaz {
 public:
  Interfaz(){};
  ~Interfaz(){};

  static const contribuyente altaRegistro() {
    contribuyente auxContribuyente;
    string auxString;

    cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | REGISTRO | "
            ">--->>-->>-->>-->>--|\n";
    cout << "\n\n\t\t\t\tINGRESE EL NOMBRE --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.nombre, auxString, T_NOMBRE);

    cout << "\n\t\t\t\tINGRESE EL APELLIDO PATERNO --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.apellido[0], auxString, T_APELLIDO);
    cout << "\n\t\t\t\tINGRESE EL APELLIDO MATERNO --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.apellido[1], auxString, T_APELLIDO);
    cout << "\n\t\t\t\tTELEFONO --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.telefono, auxString, T_TELEFONO);
    cout << "\n\t\t\t\tDIRECCION --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.direccion, auxString, T_DIRECCION);
    cout << "\n\t\t\t\tCIUDAD --> ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.ciudad, auxString, T_CIUDAD);

    cout << "\n\t\t\t\t--[FECHA DE NACIMIENTO]--\n";
    int dia, mes, anio;
    cout << "\n\t\t\t\tDIA DE NACIMIENTO --> ";
    cin >> dia;
    getchar();
    cout << "\n\t\t\t\tMES DE NACIMIENTO --> ";
    cin >> mes;
    getchar();
    cout << "\n\t\t\t\tANIO DE NACIMIENTO --> ";
    cin >> anio;
    getchar();

    auxString = normalizarFecha(dia, mes, anio);
    normalizarYGuardar(auxContribuyente.fechaNacimiento, auxString,
                       T_FECHA_NACIMIENTO);

    cout << "\n\n\t\t\t\tESTADO CIVIL (C(Casado) o S(Soltero) --> ";
    getline(cin, auxString);
    // se tiene que referenciar con &, porque es solo un caracter
    normalizarYGuardar(&auxContribuyente.estadoCivil, auxString,
                       T_ESTADO_CIVIL);
    int ndependientes;
    cout << "\n\t\t\t\tDEPENDIENTES --> ";
    cin >> ndependientes;
    getchar();
    if (ndependientes > 9) ndependientes = 9;
    auxContribuyente.dependientes = ndependientes;
    normalizarYGuardar(auxContribuyente.rfc,
                       generateKey(auxContribuyente).c_str(), T_RFC);
    cout << "\n\n\n\t\t\t|--<<--<<--<<--<<---< | REGISTRADO | "
            ">--->>-->>-->>-->>--|\n\n\n\t\t\t";

    return auxContribuyente;
  }

 private:
  static string normalizarFecha(int d, int m, int a) {
    string dia = normalizaNumero(d, 2);
    string mes = normalizaNumero(m, 2);
    string anio = normalizaNumero(a, 4);

    return dia + '/' + mes + '/' + anio;
  }
};

#endif  // INTERFAZ_H
