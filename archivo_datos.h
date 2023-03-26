#ifndef ARCHIVO_DATOS_H
#define ARCHIVO_DATOS_H

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "contribuyentes_struct.h"
using namespace std;

class ArchivoDatos : public SimpleArchivo {
public:
  ArchivoDatos(string s) : SimpleArchivo(s) { inicializaArchivo(); }
  ~ArchivoDatos() {}

  void escribirContribuyente(const contribuyente &contr) {
    // Lo convertimos a string
    string s = contr.rfc;
    s += DELIMITADOR_CAMPO;
    s += contr.nombre;
    s += DELIMITADOR_CAMPO;
    s += contr.apellido[0];
    s += DELIMITADOR_CAMPO;
    s += contr.apellido[1];
    s += DELIMITADOR_CAMPO;
    s += contr.telefono;
    s += DELIMITADOR_CAMPO;
    s += contr.direccion;
    s += DELIMITADOR_CAMPO;
    s += contr.ciudad;
    s += DELIMITADOR_CAMPO;
    s += contr.fechaNacimiento;
    s += DELIMITADOR_CAMPO;
    s += contr.estadoCivil;
    s += DELIMITADOR_CAMPO;
    s += to_string(contr.dependientes);
    // final de registro, aniadimos el DELIMITADOR_REGISTRO
    s += DELIMITADOR_REGISTRO;

    // pasamos registro a escribirRegistro, le pasamos 's'
    escribirArchivo(s);
  }

  contribuyente dameContribuyente(int direccion) {
    archivo.open(nombre_archivo, ios::in);
    archivo.seekg(direccion);

    string aux;

    // char c = archivo.get();
    // cout << "agarre: " << c << " " << int(c) << ";" << endl;

    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << aux << endl;
    getline(archivo, aux, DELIMITADOR_REGISTRO);
    cout << aux << endl;

    archivo.close();
    contribuyente cont;
    return cont;
  }
};

#endif // ARCHIVO_DATOS_H
