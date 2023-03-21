#ifndef ARCHIVO_DATOS_H
#define ARCHIVO_DATOS_H

#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'
#define NOMBRE_ARCHIVO_DATOS "HACIENDA.txt"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "contribuyentes_struct.h"
using namespace std;

class ArchivoDatos {
private:
  // Este archivo lo usaremos para insertar los nuevos registros
  fstream archivo;

public:
  ArchivoDatos(){};
  ~ArchivoDatos(){};

  void inicializaArchivo() {
    // checar si existe ios::in
    archivo.open(NOMBRE_ARCHIVO_DATOS, ios::in);
    // si falla, no existe, entonces lo creamos iso::out
    if (archivo.fail())
      archivo.open(NOMBRE_ARCHIVO_DATOS, ios::out);
    archivo.close();
  }

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
    s += normalizaNumero(contr.dependientes, 2);
    // final de registro, aniadimos el DELIMITADOR_REGISTRO
    s += DELIMITADOR_REGISTRO;
    // pasamos registro a escribirRegistro, le pasamos 's'
    escribirRegistro(s);
  }

private:
  void escribirRegistro(const string &registro) {
    archivo.open(NOMBRE_ARCHIVO_DATOS, ios::app);
    if (archivo.fail() || archivo.bad()) {
      cout << "ERROR EN ARCHIVO PRINCIPAL" << endl;
      return;
    }
    archivo << registro;
    archivo.close();
  }
};

#endif // ARCHIVO_DATOS_H
