#ifndef INDICE_PRIMARIO_H
#define INDICE_PRIMARIO_H

#define NOMBRE_ARCHIVO_INDICE_PRIMARIO "IndicePrimario.txt"

#include "contribuyentes_struct.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
struct stIndiceRfc {
  char rfc[T_RFC + 1];
  int indice; // 2 bytes (NRR)

  // constructor
  stIndiceRfc(char *rfc, int direccion) {
    // copiamos el rfc
    strcpy(this->rfc, rfc);
    // ponemos indice
    this->indice = direccion;
  }
  bool operator<(const stIndiceRfc &a) const { return this->rfc < a.rfc; }
};

class IndicePrimario {
public:
private:
  vector<stIndiceRfc> list;
  fstream archivo;

public:
  IndicePrimario(){};
  ~IndicePrimario(){};
  int insertar(char *rfc, int direccion) {
    stIndiceRfc IndiceAgregar(rfc, direccion);
    // BUSCAMOS DONDE INSERTAR
    list.insert(upper_bound(list.begin(), list.end(), IndiceAgregar),
                IndiceAgregar);

    return 1;
  }

private:
  int iniciarArchivo() {
    archivo.open(NOMBRE_ARCHIVO_INDICE_PRIMARIO, ios::in);
    if (archivo.fail()) {
      archivo.open(NOMBRE_ARCHIVO_INDICE_PRIMARIO, ios::out);
    }
    archivo.close();
    return 0;
  }
  void insertar(const stIndiceRfc &ind) {
    string buffer;
    buffer += ind.rfc;
    buffer += DELIMITADOR_REGISTRO;
    buffer += normalizaNumero(ind.indice, T_INDICE_DIRECCION);
    buffer += DELIMITADOR_REGISTRO;

    iniciarArchivo();
    archivo.open(NOMBRE_ARCHIVO_INDICE_PRIMARIO, ios::app);
    archivo << buffer;
    archivo.close();
  }
};

#endif // INDICE_PRIMARIO_H
