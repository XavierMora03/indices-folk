#ifndef CONTR_STRUCT_H
#define CONTR_STRUCT_H

// tamaños de todos los campos, así si cambia alguno el programa seguira
// funcionando con los nuevos valores.
//
#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'

#define T_RFC 13
#define T_NOMBRE 32
#define T_APELLIDO 32
#define T_TELEFONO 12
#define T_DIRECCION 45
#define T_CIUDAD 32
#define T_FECHA_NACIMIENTO 10
#define T_ESTADO_CIVIL 1
#define T_DEPENDIENTES 1

#define T_INDICE_DIRECCION 4

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct contribuyente {
  char rfc[T_RFC + 1]; // mascara (formato de captura) CCCCDDDDDDDCD
  char nombre[T_NOMBRE + 1];
  char apellido[2][T_APELLIDO + 1];
  char telefono[T_TELEFONO + 1];
  char direccion[T_DIRECCION + 1];
  char ciudad[T_CIUDAD + 1];
  char
      fechaNacimiento[T_FECHA_NACIMIENTO + 1]; // formato AAAA/MM/DD: Año, mes y
                                               //  día
  char estadoCivil;
  int dependientes;
};

void generaLlaveCanonica(contribuyente &contr) {
  // Crear una función con la forma canónica de la llave (RFC) CCCCDDDDDDDCD
  //(C=character, D= Digit)

  // ya que pusiste esta el rfc lo retornamos :)
}
// pone ceros a la izquiera de numero hasta llenar n digitos
string normalizaNumero(int numero, int digitos) {
  stringstream ss;
  ss << setw(digitos) << setfill('0') << numero;
  return ss.str();
}

class SimpleArchivo {
private:
  const string nombre_archivo;
  fstream archivo;

public:
  SimpleArchivo(string n) : nombre_archivo(n){};
  ~SimpleArchivo(){};

  void inicializaArchivo() {
    // checar si existe ios::in
    archivo.open(nombre_archivo, ios::in);
    // si falla, no existe, entonces lo creamos iso::out
    if (archivo.fail())
      archivo.open(nombre_archivo, ios::out);
    archivo.close();
  }

private:
  void escribirArchivo(const string &registro) {
    archivo.open(nombre_archivo, ios::app);
    if (archivo.fail() || archivo.bad()) {
      cout << "ERROR EN ARCHIVO PRINCIPAL" << endl;
      return;
    }
    archivo << registro;
    archivo.close();
  }
};
#endif // CONTR_STRUCT_H
