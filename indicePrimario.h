#ifndef INDICE_PRIMARIO_H
#define INDICE_PRIMARIO_H

#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "contribuyentes_struct.h"
using namespace std;

struct stIndiceRfc {
  char rfc[T_RFC + 1];
  int indice;  // 2 bytes (NRR)
  // constructor
  stIndiceRfc(const char *rfc, int direccion) {
    // copiamos el rfc
    normalizarYGuardar(this->rfc, rfc, T_RFC);
    // ponemos indice
    this->indice = direccion;
  }
  bool operator<(const stIndiceRfc &a) const {
    int res = strcmp(this->rfc, a.rfc);
    if (0 < res) return true;
    return false;
  }
  bool operator==(const stIndiceRfc &a) const {
    int res = strcmp(this->rfc, a.rfc);
    if (res == 0) return true;
    return false;
  }
};

class IndicePrimario : public SimpleArchivo {
 private:
  vector<stIndiceRfc> list;

 public:
  IndicePrimario(string s) : SimpleArchivo(s) {
    cargarIndices();
    inicializaArchivo();
  }
  ~IndicePrimario() {}

  int insertar(const char *rfc) {
    int ultimaDireccion = (list.size());
    stIndiceRfc indInsertar(rfc, ultimaDireccion);
    if (existe(rfc)) return -1;
    insertarAListaOrdenada(indInsertar);
    string registroString = registroAtexto(indInsertar);
    escribirArchivo(registroString);
    return ultimaDireccion;
  }
  int consultaIndice(const string &llave) const {
    stIndiceRfc ind(llave.c_str(), 0);
    if (!existe(llave)) {
      cout << "La llave " << llave << " no existe";
      return -1;
    }
    // encontramos el registro con upper bound, le pasamos el inicio
    // list.begin(),hasta el final list.end(), y queremos buscar la posicion de
    // ind
    auto registro = lower_bound(list.begin(), list.end(), ind);
    // como nos retoruna un puntero, usamos la flechita -> y retornamos el
    // registro->indice * el tamaño del regisrto
    return registro->indice * int(T_REGISTRO_CONTRIBUYENTE);
  }

 private:
  void insertarAListaOrdenada(const stIndiceRfc &ind) {
    list.insert(upper_bound(list.cbegin(), list.cend(), ind), ind);
  }

  string registroAtexto(stIndiceRfc &ind) {
    string buffer;
    buffer += ind.rfc;
    buffer += DELIMITADOR_CAMPO;
    buffer += normalizaNumero(ind.indice, T_INDICE_DIRECCION);
    buffer += DELIMITADOR_REGISTRO;

    return buffer;
  }

  void cargarIndices() {
    archivo.open(nombre_archivo, ios::in);

    if (archivo.fail() || archivo.bad()) {
      return;
    }

    string aux;
    while (!archivo.eof() && getline(archivo, aux)) {
      // string.substr toma dos parametros, posicion inicial (significa de donde
      // va a emezar a agarrar) y cantidad, que significa cuantos va a agarrar a
      // partir de la posiscion inicial
      //  queremos agarrar desde el inicio, y la cantidad es el tamaño de rfc
      string rfc = aux.substr(0, T_RFC);
      // ahora tenemos el rfc guardado
      // sabemos que nuestro codigo esta en la posicion inicial de T_RFC + 1,
      // iniciamos tomando de ahi, y tomamos el tamaño de la direccion
      string indice = aux.substr(T_RFC + 1, T_INDICE_DIRECCION);
      // cout << rfc << ';' << indice << ';' << endl;

      insertarAListaOrdenada(stIndiceRfc(rfc.c_str(), stoi(indice)));
    }

    archivo.close();
  }

  bool existe(const string llave) const {
    // creamos un indice, solo vamos, solo se compara la llave, por eso no
    // importa lo demás, la direccion
    stIndiceRfc ind(llave.c_str(), 0);
    return binary_search(list.begin(), list.end(), ind);
  }
};

#endif  // INDICE_PRIMARIO_H
