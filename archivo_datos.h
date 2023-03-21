#ifndef ARCHIVO_DATOS_H
#define ARCHIVO_DATOS_H

#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'
#define NOMBRE_ARCHIVO_DATOS "hacienda.txt"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "contribuyentes_struct.h"
using namespace std;

class ArchivoDatos {
private:
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
    // convertimos el struct a texto con generarTextoRegistro
    const char *localizacionCadena = generarTextoRegistro(contr);
    // el texto convertido, (lo tenemos en localizacionCadena) lo pasamos a
    // nuestra funcion que escribe escribirRegistro
    escribirRegistro(localizacionCadena);
  }

private:
  const char *generarTextoRegistro(const contribuyente &contr) {
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
    s += contr.estadoCivil;
    s += DELIMITADOR_CAMPO;
    s += normalizaNumero(contr.dependientes, 2);
    // final de registro, aniadimos el DELIMITADOR_REGISTRO
    s += DELIMITADOR_REGISTRO;
    // retormanmos el puntero donde esta la cadena, convirtiendolo con el metodo
    // c_str() de s
    return s.c_str();
  }
  void escribirRegistro(const char *registro) {
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
