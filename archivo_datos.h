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

  void muestraContribuyente(int direccion) {
    archivo.open(nombre_archivo, ios::in);
    archivo.seekg(direccion);

    string aux;

    cout << "MOSTRANDO CONTRIBUYENTE" << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tRFC: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tNombre: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tApellido paterno: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tApellido materno: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tTelefono: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tDireccion: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tCiudad: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tFecha nacimiento: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tEstado civil: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_CAMPO);
    cout << "\t\t\t\tDependientes: " << aux << endl;
    getline(archivo, aux, DELIMITADOR_REGISTRO);

    archivo.close();
  }
};

#endif  // ARCHIVO_DATOS_H
