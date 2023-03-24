#ifndef INDICE_PRIMARIO_H
#define INDICE_PRIMARIO_H

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
  bool operator<(const stIndiceRfc &a) const { return (this->rfc < a.rfc); }
};

class IndicePrimario : public SimpleArchivo {
private:
  vector<stIndiceRfc> list;

public:
  IndicePrimario(string s) : SimpleArchivo(s) {}
  ~IndicePrimario() {}

  int insertar(char *rfc, int direccion) {
    stIndiceRfc auxIndice(rfc, direccion);
    list.insert(upper_bound(list.begin(), list.end(), auxIndice), auxIndice);

    string registroString = registroAtexto(auxIndice);
    escribirArchivo(registroString);
    return 1;
  }

private:
  string registroAtexto(const stIndiceRfc &ind) {
    string buffer;
    buffer += ind.rfc;
    buffer += DELIMITADOR_CAMPO;
    buffer += normalizaNumero(ind.indice, T_INDICE_DIRECCION);
    buffer += DELIMITADOR_REGISTRO;

    return buffer;
  }

  void cargarIndice() {}
};

#endif // INDICE_PRIMARIO_H
