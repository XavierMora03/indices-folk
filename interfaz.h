// my_class.h
#ifndef INTERFAZ_H // include guard
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

  static const void mostrarRegistro(const contribuyente &contr) {
    cout << "RFC: " << contr.rfc << endl;
    cout << "Nombre: " << contr.nombre << endl;
    cout << "Apellido paterno: " << contr.apellido[0] << endl;
    cout << "Apellido materno: " << contr.apellido[1] << endl;
    cout << "Telefono: " << contr.telefono << endl;
    cout << "Direccion: " << contr.direccion << endl;
    cout << "Ciudad: " << contr.ciudad << endl;
    cout << "Fecha nacimiento: " << contr.fechaNacimiento << endl;
    cout << "Estado civil: " << contr.estadoCivil << endl;
    cout << "Dependientes: " << contr.dependientes << endl;
  }

  // no se si el const afecte
  static const contribuyente altaRegistro() {
    contribuyente auxContribuyente;
    string auxString;
    cout << "ALTA REGISTRO" << endl;
    cout << "Ingrese RFC: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.rfc, auxString, T_RFC);
    cout << "Ingrese el nombre: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.nombre, auxString, T_NOMBRE);
    cout << "Ingrese apellido paterno: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.apellido[0], auxString, T_APELLIDO);
    cout << "Ingrese apellido materno: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.apellido[1], auxString, T_APELLIDO);
    cout << "Ingrese el telefono: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.telefono, auxString, T_TELEFONO);
    cout << "Ingrese direccion: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.direccion, auxString, T_DIRECCION);
    cout << "Ingrese ciudad: ";
    getline(cin, auxString);
    normalizarYGuardar(auxContribuyente.ciudad, auxString, T_CIUDAD);

    int dia, mes, anio;
    cout << "Ingrese dia de nacimiento: ";
    cin >> dia;
    getchar();
    cout << "Ingrese mes de nacimiento: ";
    cin >> mes;
    getchar();
    cout << "Ingrese año de nacimiento: ";
    cin >> anio;
    getchar();

    auxString = normalizarFecha(dia, mes, anio);
    normalizarYGuardar(auxContribuyente.fechaNacimiento, auxString,
                       T_FECHA_NACIMIENTO);
    cout << "Ingrese estado civil (C ó S): ";
    getline(cin, auxString);
    // se tiene que referenciar con &, porque es solo un caracter
    normalizarYGuardar(&auxContribuyente.estadoCivil, auxString,
                       T_ESTADO_CIVIL);
    int ndependientes;
    cout << "Ingresa el numero de dependientes: ";
    cin >> ndependientes;
    getchar();
    if (ndependientes > 9)
      ndependientes = 9;
    auxContribuyente.dependientes = ndependientes;

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

#endif // INTERFAZ_H
